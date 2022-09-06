CODE_SELECTOR  equ  0x08
DATA_SELECTOR  equ  0x10

extern guest_main

section .entrypoint

[BITS 16]
cli                          ; disable hardware interrupts (since no IDT loaded yet)

lgdt [gdt_descriptor]        ; load GDT (see segments defined after gdt_start below)

; switch to protected mode (32-bits mode)
mov     eax,cr0 
or      eax,1                ; set PE (Protection Enable) bit in CR0 (Control Register 0)
mov     cr0,eax

jmp     CODE_SELECTOR:flush  ; far jump [selector:offset] to load code segment (cs) with code descriptor in GDT
flush:

[BITS 32]
mov     ax,DATA_SELECTOR     ; update data (ds), stack (sp) and extra (es) segments with data descriptor in GDT
mov     ds,ax
mov     ss,ax
mov     es,ax

call    guest_main           ; call guest C code entrypoint
hlt                          ; halt the CPU

; Setup a GDT table to identity map the full 4GB address space (32 bits)
gdt_start:                   ; the GDT table starts here
	
gdt_null:                    ; 1st descriptor: NULL descriptor (required)
    	dd 0
		dd 0

gdt_code:                    ; 2nd descriptor: code descriptor: base=0, limit=0xFFFFF (4GB)
		dw 0xFFFF            ; limit (bits 0-15)
		dw 0                 ; base (bits 0-15)
		db 0                 ; base (bits 16-23)
		db 10011001b         ; bit    7: P: present in memory
		                     ; bits 5-6: DPL: privilege level (ring level)
							 ; bit    4: S: 1 for segments, 0 for system (TSS, LDT, gates)
							 ; bit  0-3: Type: 1001b (9) for code exec only
		db 11001111b         ; bits 4-7: flags:
		                     ;   bit 7: G: granularity (0=1 byte, 1=4KB)
							 ;   bit 6: D: 1 for 32-bit code and data segments; 0 for system (TSS, LDT, gate)
							 ;   bit 5: must be 0
							 ;   bit 4: available for use
		                     ; bits 0-3: limit (bits 16-19)
		db 0                 ; base (bits 24-31)
	
gdt_data:                    ; 3rd descriptor: data descriptor: base=0, limit=0xFFFFF (4GB)
		dw 0xFFFF            ; limit (bits 0-15)
		dw 0                 ; base (bits 0-15)
		db 0                 ; base (bits 16-23)
		db 10010011b         ; bit    7: P: present in memory
		                     ; bits 5-6: DPL: privilege level (ring level)
							 ; bit    4: S: 1 for segments, 0 for system (TSS, LDT, gates)
							 ; bit  0-3: Type: 0011b (3) data read/write
		db 11001111b         ; bits 4-7: flags:
		                     ;   bit 7: G: granularity (0=1 byte, 1=4KB)
							 ;   bit 6: D: 1 for 32-bit code and data segments; 0 for system (TSS, LDT, gate)
							 ;   bit 5: must be 0
							 ;   bit 4: available for use
		                     ; bits 0-3: limit (bits 16-19)
		db 0                 ; base (bits 24-31)

gdt_end:

gdt_descriptor:                  ; descriptor pointing to the GDT (required by the lgdt instruction)
    dw gdt_end - gdt_start - 1   ; GDT size minus 1
    dd gdt_start                 ; address of the GDT table
