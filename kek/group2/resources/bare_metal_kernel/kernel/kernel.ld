ENTRY(entrypoint)            /* the entry point */

SECTIONS {
	/* All sections located above 1MB */
    . = 0x100000;

	/* multiboot section first (must reside in the first 8KB otherwise GRUB won't find it!) */
    .multiboot ALIGN(4): { *(.multiboot) }
    .text ALIGN(4): { *(.text) }
    
	/* Read-only data section */
    .rodata ALIGN(4): { *(.rodata) }

    /* Read-write data sections (initialized and unitialized) */
    .data ALIGN(4): { *(.data) }
    .bss ALIGN(4): { *(.bss) }
    
    /* Stack section (16 byte-aligned to be compliant with the UNIX SYSTEM V ABI) */
    .stack ALIGN(16): { *(.stack) }
}
