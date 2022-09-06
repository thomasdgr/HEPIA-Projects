global entrypoint  ; the entry point symbol defined in kernel.ld

extern kernel_main

STACK_SIZE                equ 0x100000     ; 1MB of stack

; Values for the multiboot header
MULTIBOOT_MAGIC        equ 0x1BADB002  ; multiboot magic value
MULTIBOOT_ALIGN        equ 1   ; load kernel and modules on page boundary
MULTIBOOT_MEMINFO      equ 2   ; provide kernel with memory info
MULTIBOOT_VIDEO_MODE   equ 4   ; ask grub to switch to SVGA graphics modes

MULTIBOOT_FLAGS        equ (MULTIBOOT_ALIGN|MULTIBOOT_MEMINFO)

; Magic + checksum + flags must equal 0!
MULTIBOOT_CHECKSUM     equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

;---------------------------------------------------------------------------------------------------
; .multiboot section
; This section must be located at the very beginning of the kernel image.

section .multiboot

; Mandatory part of the multiboot header
; see http://git.savannah.gnu.org/cgit/grub.git/tree/doc/multiboot.h?h=multiboot
dd MULTIBOOT_MAGIC
dd MULTIBOOT_FLAGS
dd MULTIBOOT_CHECKSUM

; for MULTIBOOT_MEMORY_INFO
dd 0x00000000    ; header_addr
dd 0x00000000    ; load_addr
dd 0x00000000    ; load_end_addr
dd 0x00000000    ; bss_end_addr
dd 0x00000000    ; entry_addr

entrypoint:
		; Bootloader code starts executing here
		cli  ; disable hardware interruptions

		mov     esp,stack          ; initialize stack pointer (remember: stack grows downward)
		mov     ebp,esp
		push	ebx                ; GRUB pushes a pointer to its configuration into ebx => pass it to our kernel
		call    kernel_main        ; call the C kernel

.forever:                          ; should never return from kernel_main
		hlt
		jmp .forever

;-----------------------------------------------------------------------------------------------------------------------
; Stack section
; nobits indicates value in the section aren't initialized (as with .bss)
section .stack nobits

resb STACK_SIZE  ; reserve a contiguous space of STACK_SIZE bytes
stack:
