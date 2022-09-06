BAREMETAL_FLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -fno-pie -static -O3
CC=gcc -std=gnu11 $(BAREMETAL_FLAGS) -Wall -Wextra -MMD -Ishared -I../.. -I..
LD=gcc -Tshared/guest.ld $(BAREMETAL_FLAGS)

C_SRCS=$(wildcard shared/*.c)
C_OBJS=$(C_SRCS:.c=.o)
C_DEPS=$(C_OBJS:%.o=%.d)

ASM_SRCS=$(wildcard shared/*.s)
ASM_OBJS=$(ASM_SRCS:.s=.o)

test_vga_emul.bin: $(C_OBJS) $(ASM_OBJS) test_vga_emul.o
	$(LD) $^ -o $@

test_vga_pv.bin: $(C_OBJS) $(ASM_OBJS) test_vga_pv.o
	$(LD) $^ -o $@

test_disk_emul.bin: $(C_OBJS) $(ASM_OBJS) test_disk_emul.o
	$(LD) $^ -o $@

test_disk_pv.bin: $(C_OBJS) $(ASM_OBJS) test_disk_pv.o
	$(LD) $^ -o $@

benchmark_disk_emul.bin: $(C_OBJS) $(ASM_OBJS) benchmark_disk_emul.o
	$(LD) $^ -o $@

benchmark_disk_pv.bin: $(C_OBJS) $(ASM_OBJS) benchmark_disk_pv.o
	$(LD) $^ -o $@


%.o: %.c
	$(CC) -c $< -o $@

%.o: %.s
	nasm -f elf32 $< -o $@

clean:
	rm -f $(C_OBJS) $(ASM_OBJS) $(C_DEPS) *.o *.d *.bin

.PHONY: clean

-include $(C_DEPS)
