global outb
global inb
global outw
global inw
global outd
global ind

section .text                      ; start of the text (code) section
align 4                            ; the code must be 4 byte aligned

; void outb(uint16_t port, uint8_t data);
outb:
    mov     dx,word [esp+4]    ; port (2 bytes)
    mov     al,byte [esp+8]    ; data (1 byte)
    out     dx,al
    ret

; uint8_t inb(uint16_t port);
inb:
    mov     dx,word [esp+4]    ; port (2 bytes)
    in      al,dx
    ret

; void outw(uint16_t port, uint16_t data);
outw:
    mov     dx,word [esp+4]    ; port (2 bytes)
    mov     ax,word [esp+8]    ; data (2 bytes)
    out     dx,ax
    ret

; uint16_t inw(uint16_t port);
inw:
    mov     dx,word [esp+4]    ; port (2 bytes)
    in      ax,dx
    ret

; void outd(uint16_t port, uint32_t data);
outd:
    mov     dx,word [esp+4]    ; port (2 bytes)
    mov     eax,[esp+8]        ; data (4 bytes)
    out     dx,eax
    ret

; uint32_t ind(uint16_t port);
ind:
    mov     dx,word [esp+4]    ; port (2 bytes)
    in      eax,dx
    ret
