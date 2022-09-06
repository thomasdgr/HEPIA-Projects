OUTPUT_FORMAT("binary")

SECTIONS {
	. = 0;         /* first section located at address 0 */

	.entrypoint ALIGN(4):   /* entry point: must be located at 0 */
	{
		*(.entrypoint)
	}

	.text ALIGN(4) :        /* code */
	{
		*(.text*)
	}

	.rodata ALIGN(4) :      /* read-only data */
	{
		*(.rodata*)          
	}

	.data ALIGN(4) :        /* initialized data */
	{
		*(.data*)
	}

	.bss ALIGN(4) :         /* unitialized data */
	{
		*(COMMON)
		*(.bss*)
	}
}
