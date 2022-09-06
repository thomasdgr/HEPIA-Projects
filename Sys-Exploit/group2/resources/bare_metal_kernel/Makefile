QEMU=qemu-system-i386 -enable-kvm -m 128
ISO_NAME=yoctos.iso
GRUB_CONF=grub/grub.cfg
GRUB_MKRESCUE_ARGS=/usr/lib/grub/i386-pc
CC_FLAGS=-g -O0
LD_FLAGS=-g

help:
	@echo "Available targets:"
	@echo "run      build the OS ISO image and run it in QEMU"
	@echo "iso      build the OS ISO image"
	@echo "kernel   build the kernel only"
	@echo "debug    build the OS ISO image and run it in QEMU for debugging"
	@echo "clean    clean up everything"

iso: $(ISO_NAME)

msg:
	@echo "================================================="
	@echo "Build targeting a $(PLATFORM)/$(SYSTEM) platform" 
	@echo "================================================="

run: $(ISO_NAME)
	$(QEMU) -cdrom $<

# The "accel=tcg" option is necessary to be able to debug an ELF within QEMU
debug: $(ISO_NAME)
	$(QEMU) -s -S -cdrom $< -machine accel=tcg

# ISO image creation taken from http://wiki.osdev.org/Bare_Bones#Booting_the_Kernel
# Requires grub-mkrescue and xorriso
# NOTE: on hosts that boot via UEFI, the path /usr/lib/grub/i386-pc is required
# by grub-mkrescue otherwise the ISO won't be bootable by qemu.
$(ISO_NAME): msg $(GRUB_CONF) kernel
	mkdir -p build/boot/grub
	cp $(GRUB_CONF) build/boot/grub/
	cp kernel/kernel.elf build/boot/
	grub-mkrescue $(GRUB_MKRESCUE_ARGS) -o $@ build

kernel:
	$(MAKE) -C $@ CC_FLAGS="$(CC_FLAGS)" LD_FLAGS="$(LD_FLAGS)"

clean:
	/bin/rm -rf build $(ISO_NAME)
	$(MAKE) -C kernel clean

.PHONY: clean kernel
