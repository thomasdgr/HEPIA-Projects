BAREMETAL_FLAGS=-m32 -ffreestanding -nostdlib -fno-builtin -fno-stack-protector -fno-pie -static
CC=gcc -std=gnu11 $(BAREMETAL_FLAGS) -Wall -Wextra -MMD -c
LD=gcc

override LD_FLAGS+=-Tkernel.ld $(BAREMETAL_FLAGS) -lgcc

KERNEL_C_SRC=$(shell find . -iname "*.c")
KERNEL_ASM_SRC=$(shell find . -iname "*.s")
KERNEL_C_OBJ=$(KERNEL_C_SRC:.c=.o)
KERNEL_ASM_OBJ=$(KERNEL_ASM_SRC:.s=.o)

KERNEL_OUT=kernel.elf

DEP=$(KERNEL_C_OBJ:%.o=%.d)

all: $(KERNEL_OUT)

%.o: %.c
	$(CC) $(CC_FLAGS) $(CC_DEFINES) -I. -I.. $< -o $@

%.o: %.s
	nasm -f elf32 $< -o $@

$(KERNEL_OUT): $(KERNEL_C_OBJ) $(KERNEL_ASM_OBJ)
	$(LD) $^ -o $@ $(LD_FLAGS)

clean:
	find . -name "*.o" -delete -or -name "*.d" -delete
	/bin/rm -f $(KERNEL_OUT)

.PHONY: clean

-include $(DEP)
