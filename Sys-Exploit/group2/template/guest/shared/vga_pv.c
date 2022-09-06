#include "pmio.h"
#include "vga.h"
#include "hypercall.h"

pv_vga_char* const pv_buf = (pv_vga_char*) PV_ADDR;

// Write a character using paravirtualization
void putchar_pv(int x, int y, char ch, color_t fg, color_t bg) {
	pv_vga_char c = {(uint8_t)ch, bg, fg, x,y};
	*pv_buf= c;
	outb(0xABBA, VGA);  // write 1 char
}
