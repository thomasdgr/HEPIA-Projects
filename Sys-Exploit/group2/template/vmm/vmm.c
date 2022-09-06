/**
* @file vmm.c
* @brief Hypervisor KVM API to manage guest vm
*
* Manage guest vm both mmio and pmio, manage the memory mapping, 
* the display with SDL and threading with the vm
*
* @author Rod Quentin, Dagier Thomas
* @bug No known bugs.
* @date 02.04.2022
* @version 1.0
*/

// KVM API reference: https://www.kernel.org/doc/html/latest/virt/kvm/api.html
// Code initially based on example from https://lwn.net/Articles/658511/

#include <err.h>
#include <fcntl.h>
#include <linux/kvm.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <sys/eventfd.h>
#include <unistd.h>

#include <errno.h>
#include <pthread.h>
#include "vga_vmm.h"
#include "disk_vmm.h"
#include "hypercall.h"

#define FB_ADDR 0xB8000 // the address of the VGA framebuffer

// the given structure of the vm to run
typedef struct {
	int vmfd;
	int vcpufd;

	struct kvm_run *run;
	int vcpu_mmap_size;

	uint8_t *guest_ram_mem;
	u_int guest_ram_mem_size;
    uint8_t *guest_mmio_mem;
	u_int guest_mmio_mem_size;
    uint8_t *guest_pv_mem;
	u_int guest_pv_mem_size;
} vm_t;

// file descriptor of KVM device
int kvm_fd = 0;
// the framebuffer used to store data we want to display
static vga_char vga_char_buf[FB_XRES * FB_YRES];

/**
* manage the shared framebuffer with pmio handler
* @param src the content to add on the framebuffer
*/
void hypercall_vga(void* src){
    pv_vga_char pv_char = *((pv_vga_char*)src);
    uint32_t offset = pv_char.y * FB_XRES + pv_char.x;
    vga_char_buf[offset].ascii_char = pv_char.ascii_char;
    vga_char_buf[offset].bg_color = pv_char.bg_color;
    vga_char_buf[offset].char_color = pv_char.char_color;
}

/**
* manage the disk writing with pmio handler
* @param src the content to write in the disk
*/
void hypercall_disk(void* src){
    pv_disk* pv_disk_content = (pv_disk*)src;
    if(disk_write((char*)pv_disk_content->data, pv_disk_content->sector) != 0){
        fprintf( stderr, "Could not write on disk\n");
    }
}

// array of hypercall function to call (generic way to add hypercall functions)
// TO ADD AN OTHER HYPERCALL, ADD HIS FUNCTION BELLOW 
static void (*hypercall_func[])(void* src) = {
    // this must match with the order in hypercall_t structure
    hypercall_vga,
    hypercall_disk,
};

/**
* PMIO handler
* @param vm the vm that made a pmio update
*/
static void handle_pmio(vm_t *vm) {
	struct kvm_run *run = vm->run;
    // Guest wrote to an I/O port
    if (run->io.direction == KVM_EXIT_IO_OUT) {
        uint8_t *addr_pmio = (uint8_t *)run + run->io.data_offset;
        uint8_t nb_bytes = run->io.size;
        uint32_t val_written;
        switch (nb_bytes) {
            case 1:  // retrieve the 8-bit value written by the guest
                val_written = *(uint8_t *)addr_pmio;
                break;
            case 2:  // retrieve the 16-bit value written by the guest
                val_written = *(uint16_t *)addr_pmio;
                break;
            default:
                fprintf(stderr, "VMM: Unsupported size in KVM_EXIT_IO\n");
                val_written = 0;
        }
        if( run->io.port == 0xABBA){
            hypercall_func[val_written](vm->guest_pv_mem);
        }else if (run->io.port >= 0x1F0 && run->io.port <= 0x1F7){
            disk_machine_state_writing_from_guest(run->io.port, val_written, nb_bytes);
        }
    }
    // Guest read from an I/O port
    else if (run->io.direction == KVM_EXIT_IO_IN) {
        uint8_t *addr_pmio = (uint8_t *)run + run->io.data_offset;
        uint8_t val_to_give = disk_machine_state_reading_from_guest(run->io.port);
        *addr_pmio = val_to_give;
        //printf("VMM: PMIO guest read: size=%d port=0x%x [value injected by VMM=0x%x]\n", run->io.size, run->io.port, val_to_give);
    }
    else
        fprintf(stderr, "VMM: unhandled KVM_EXIT_IO\n");
}

/**
* MMIO handler
* @param vm the vm that made a pmio update
*/
static void handle_mmio(vm_t *vm) {
	struct kvm_run *run = vm->run;
    // Guest wrote to an MMIO address (i.e. a memory slot marked as read-only)
    if (run->mmio.is_write) {
        uint32_t val_written_mmio;
        switch (run->mmio.len) {
            case 1:
                val_written_mmio = *((uint8_t *)run->mmio.data);
                break;
            case 2:
                val_written_mmio = *((uint16_t *)run->mmio.data);
                break;
            case 4:
                val_written_mmio = *((uint32_t *)run->mmio.data);
                break;
            default:
                fprintf(stderr, "VMM: Unsupported size in KVM_EXIT_MMIO\n");
                val_written_mmio = 0;
        }
        //printf("VMM: MMIO guest write: len=%d addr=%ld value=%d\n", run->mmio.len, (long int)run->mmio.phys_addr, val_written_mmio);
        if(run->mmio.phys_addr >= FB_ADDR && run->mmio.phys_addr < FB_ADDR + (FB_SIZE * sizeof(uint16_t))){
            uint32_t addr_offset = run->mmio.phys_addr - FB_ADDR;
            // When address is odd, it means that value length is 1 byte. So, minus 1 because previous adress point to ascii_char. 
            // Now we want attribute and is in the same index in the array.
            uint32_t vga_char_buf_index = addr_offset % 2 == 0 ? addr_offset: (addr_offset-1);
            // Divide by 2 because one data in vga_char_buf array correspond to two bytes. 
            vga_char_buf_index /= 2;
            if(run->mmio.len == 1){
                if(addr_offset % 2 == 0){
                    vga_char_buf[vga_char_buf_index].ascii_char = val_written_mmio; 
                }else{
                    vga_char_buf[vga_char_buf_index].bg_color = (val_written_mmio >> 4); 
                    vga_char_buf[vga_char_buf_index].char_color = (val_written_mmio & 0xF);
                }
            }else{
                for(uint32_t i = 0; i < run->mmio.len; i+=2){
                     vga_char_buf[vga_char_buf_index].ascii_char = val_written_mmio; 
                     uint8_t attribute = val_written_mmio >> 8; 
                     vga_char_buf[vga_char_buf_index].bg_color = (attribute >> 4);
                     vga_char_buf[vga_char_buf_index].char_color =(attribute & 0xF);
                    // One adress gives 1 byte, so we want to skip to next character, 2 bytes after.
                     vga_char_buf_index +=1;
                     val_written_mmio = val_written_mmio >> 16;
                }
            }
        }
    }
}

static void check_capability(int kvm, int cap, char *cap_string) {
    if (!ioctl(kvm, KVM_CHECK_EXTENSION, cap))
    	errx(1, "VMM: Required extension %s not available", cap_string);
}

/**
* create a vm representation of the binary given with memory allocation and mapping,
* vCPU, RAM, framebuffer and pmio shared framebuffer.
* @param guest_binary the binary of the guest to run
* @return the structure of the VM if she's created succesfully, else NULL
*/
static vm_t* vm_create(const char *guest_binary) {

	vm_t *vm = malloc(sizeof(vm_t));
    if (!vm) err(1, NULL);
    memset(vm, 0, sizeof(vm_t));

    char kvm_dev[] = "/dev/kvm";
    kvm_fd = open(kvm_dev, O_RDWR | O_CLOEXEC);
    if (kvm_fd < 0) err(1, "%s", kvm_dev);

    // Make sure we have the right version of the API
    int version = ioctl(kvm_fd, KVM_GET_API_VERSION, NULL);
    if (version < 0) err(1, "VMM: KVM_GET_API_VERSION");
    if (version != KVM_API_VERSION) err(1, "VMM: KVM_GET_API_VERSION %d, expected %d", version, KVM_API_VERSION);

    vm->vmfd = ioctl(kvm_fd, KVM_CREATE_VM, 0);
    if (vm->vmfd < 0) err(1, "VMM: KVM_CREATE_VM");

    // Make sure we can manage guest physical memory slots
	check_capability(kvm_fd, KVM_CAP_USER_MEMORY, "KVM_CAP_USER_MEMORY");

    // mmap syscall:
    // 1st arg: specifies at which virtual address to start the mapping; if NULL, kernel chooses the address
    // 2nd arg: size to allocate (in bytes)
    // 3rd arg: access type (read, write, etc.)
    // 4th arg: flags; MAP_ANONYMOUS = mapping not backed by any file and contents initialized to zero
    // 5th arg: file descriptor if mmap a file (otherwise, set to -1)
    // 6th arg: offset when mmap a file
	// IMPORTANT: size must be a multiple of a page (4KB) and address must be on a page boundary!

    // Allocate 256kB of RAM for the guest RAM(stack) + binary
    vm->guest_ram_mem_size = 64*4096;
    vm->guest_ram_mem = mmap(NULL, vm->guest_ram_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!vm->guest_ram_mem) err(1, "VMM: allocating guest memory");

    // Allocate frame buffer
    vm->guest_mmio_mem_size = FB_SIZE * sizeof(uint16_t) + 96; // Needed because pages are 4kB
    vm->guest_mmio_mem = mmap(NULL,  vm->guest_mmio_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!vm->guest_mmio_mem) err(1, "VMM: allocating shared frame buffer (VGA MMIO)");

     // Allocate Paravirtualized buffer
    vm->guest_pv_mem_size = vm->guest_mmio_mem_size;
    vm->guest_pv_mem = mmap(NULL,  vm->guest_pv_mem_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (!vm->guest_pv_mem) err(1, "VMM: allocating shared PMIO");

    // Retrieve binary file
    FILE *binary_file;
    binary_file = fopen(guest_binary,"rb");
    if (!binary_file) {
        perror("fopen");
        return NULL;
    }
     struct stat stat_binary;
    if (stat(guest_binary, &stat_binary) == -1) {
        perror("stat");
       return NULL;
    }
    if( fread(vm->guest_ram_mem, stat_binary.st_size, 1, binary_file) == 0){
        perror("read nothing");
        return NULL;
    }
    fclose(binary_file);
    //--------------------------

	// Map guest_ram_mem to physical address 0 in the guest address space
    struct kvm_userspace_memory_region mem_region1 = {
        .slot = 0,
        .guest_phys_addr = 0,
        .memory_size = vm->guest_ram_mem_size,
        .userspace_addr = (uint64_t)vm->guest_ram_mem,
        .flags = 0
    };
    if (ioctl(vm->vmfd, KVM_SET_USER_MEMORY_REGION, &mem_region1) < 0) err(1, "VMM: KVM_SET_USER_MEMORY_REGION, slot 0");
    // Map VMM frame buffer to address 0xB8000 in the guest address space
    struct kvm_userspace_memory_region mem_region2 = {
        .slot = 1,
        .guest_phys_addr = FB_ADDR,
        .memory_size = vm->guest_mmio_mem_size,
        .userspace_addr = (uint64_t)vm->guest_mmio_mem,
        .flags = KVM_MEM_READONLY
    };
    if (ioctl(vm->vmfd, KVM_SET_USER_MEMORY_REGION, &mem_region2) < 0) err(1, "VMM: KVM_SET_USER_MEMORY_REGION, slot 1");
    //Map VMM frame buffer to address 0xB9000 in the guest address space    
    struct kvm_userspace_memory_region mem_region3 = {
        .slot = 2,
        .guest_phys_addr = PV_ADDR,
        .memory_size = vm->guest_pv_mem_size,
        .userspace_addr = (uint64_t)vm->guest_pv_mem,
        .flags = 0
    };
    if (ioctl(vm->vmfd, KVM_SET_USER_MEMORY_REGION, &mem_region3) < 0) err(1, "VMM: KVM_SET_USER_MEMORY_REGION, slot 2");
    
    // Create the vCPU
    vm->vcpufd = ioctl(vm->vmfd, KVM_CREATE_VCPU, 0);
    if (vm->vcpufd < 0) err(1, "VMM: KVM_CREATE_VCPU");

    // Setup memory for the vCPU
    vm->vcpu_mmap_size = ioctl(kvm_fd, KVM_GET_VCPU_MMAP_SIZE, NULL);
    if (vm->vcpu_mmap_size < 0) err(1, "VMM: KVM_GET_VCPU_MMAP_SIZE");
    if (vm->vcpu_mmap_size < (int)sizeof(struct kvm_run)) err(1, "VMM: KVM_GET_VCPU_MMAP_SIZE unexpectedly small");
    vm->run = mmap(NULL, (size_t)vm->vcpu_mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, vm->vcpufd, 0);
    if (!vm->run) err(1, "VMM: mmap vcpu");

    // Initialize CS to point to 0
    struct kvm_sregs sregs;
    if (ioctl(vm->vcpufd, KVM_GET_SREGS, &sregs) < 0) err(1, "VMM: KVM_GET_SREGS");
	sregs.cs.base = 0;
	sregs.cs.selector = 0;
	if (ioctl(vm->vcpufd, KVM_SET_SREGS, &sregs) < 0) err(1, "VMM: KVM_SET_SREGS");

    // Initialize instruction pointer and flags register
    struct kvm_regs regs;
	memset(&regs, 0, sizeof(regs));
	regs.rsp = vm->guest_ram_mem_size;  // set stack pointer at the top of the guest's RAM
	regs.rip = 0;
	regs.rflags = 0x2;  // bit 1 is reserved and should always bet set to 1
    if (ioctl(vm->vcpufd, KVM_SET_REGS, &regs) < 0) err(1, "VMM: KVM_SET_REGS");

	return vm;
}

/**
* vCPU thread that runs a vm with parameters given in a structure (vm_t*)
* @param p the vm structure to run
* @return NULL on error or canceled by the user
*/
void* vm_run(void* p){
    int error_code = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
     if (error_code != 0) {
        perror("Thread pthread_setcancelstate failed\n");
        return NULL;
    }
    vm_t* vm = (vm_t*)p;
    // Runs the VM (guest code) and handles VM exits
    while (1) {
		// Runs the vCPU until encoutering a VM_EXIT
        if (ioctl(vm->vcpufd, KVM_RUN, NULL) < 0) err(1, "VMM: KVM_RUN");
        switch (vm->run->exit_reason) {
			// NOTE: KVM_EXIT_IO is significantly faster than KVM_EXIT_MMIO
            case KVM_EXIT_IO:    // encountered an I/O instruction
                handle_pmio(vm);
                break;
            case KVM_EXIT_MMIO:  // encountered a MMIO instruction which could not be satisfied
                handle_mmio(vm);
                break;
            case KVM_EXIT_HLT:   // encountered "hlt" instruction
                fprintf(stderr, "VMM: KVM_EXIT_HLT\n");
				return NULL;
            case KVM_EXIT_FAIL_ENTRY:
                fprintf(stderr, "VMM: KVM_EXIT_FAIL_ENTRY: hardware_entry_failure_reason = 0x%llx\n",
                    (unsigned long long)vm->run->fail_entry.hardware_entry_failure_reason);
                break;
            case KVM_EXIT_INTERNAL_ERROR:
                fprintf(stderr, "VMM: KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n", vm->run->internal.suberror);
				return NULL;
			case KVM_EXIT_SHUTDOWN:
                fprintf(stderr, "VMM: KVM_EXIT_SHUTDOWN\n");
				return NULL;
            default:
                fprintf(stderr, "VMM: unhandled exit reason (0x%x)\n", vm->run->exit_reason);
				return NULL;
        }
    }
}

/**
* vCPU thread that runs a vm with parameters given in a structure (vm_t*)
* @param vm the vm structure to destroy
* @return 0 on success, else -1
*/
static int vm_destroy(vm_t *vm) {
    if (vm->guest_ram_mem)
        munmap(vm->guest_ram_mem, vm->guest_ram_mem_size);
    if (vm->guest_mmio_mem)
        munmap(vm->guest_mmio_mem, vm->guest_mmio_mem_size);
    if (vm->guest_pv_mem)
        munmap(vm->guest_pv_mem, vm->guest_pv_mem_size);
    if (vm->run)
        munmap(vm->run, vm->vcpu_mmap_size);
    memset(vm, 0, sizeof(vm_t));
    free(vm);
    close(kvm_fd);
    if (kvm_fd < 0){
        perror("fopen");
        return -1;
    }
    return 0;
}

/**
* Program main entry
* @param argc should be 5
* @param argv array of arguments like the binary of the vm to run or the disk to open for the guest vm
* @return EXIT_SUCCESS on success, else EXIT_FAILURE
*/
int main(int argc, char **argv) {
    if(argc != 5){
         fprintf(stderr, "Bad usage. Please use: vmm -guest BIN -disk FILE\n");
         return EXIT_FAILURE;
    } else{
        char* bin_file_name = argv[2];
        char* disk_file_name = argv[4];
        bool is_vga_bin = strstr(bin_file_name, "vga"); //contains "vga"
        bool is_disk_bin = strstr(bin_file_name, "disk"); //contains "disk"
        pthread_t pthread_vga;
        pthread_t pthread_vm;
        if(is_disk_bin){
            if(disk_init(disk_file_name) != 0){
                fprintf( stderr, "Disk cannot be opened\n" );
                return EXIT_FAILURE;
            }
        }
        if(is_vga_bin){
  	        if(pthread_create(&pthread_vga, NULL, vga_thread_display, (void*)vga_char_buf) != 0){
                  fprintf( stderr, "Failed to create VGA thread\n" );
                  return EXIT_FAILURE;   
              }
        }
        vm_t *vm = vm_create(bin_file_name);
        if(vm == NULL)
            return EXIT_FAILURE;
        if( pthread_create(&pthread_vm, NULL, vm_run, (void*)vm) != 0){
            fprintf( stderr, "Failed to create vCPU thread\n" );
            return EXIT_FAILURE;  
        }
        if(is_vga_bin){
            pthread_join(pthread_vga, NULL);
            //vCPU thread is blocked in ioctl only with VGA, otherwise HLT instruction
            if(pthread_cancel(pthread_vm) != 0){
                fprintf( stderr, "Failed to cancel vCPU thread\n" );
                return EXIT_FAILURE;  
            }
        }
        pthread_join(pthread_vm, NULL);
        if(is_disk_bin){
            if(disk_free() != 0){
                fprintf( stderr, "Disk cannot be closed\n" );
                return EXIT_FAILURE;
            }
        }
        if(vm_destroy(vm) != 0)
            return EXIT_FAILURE;
    }
}