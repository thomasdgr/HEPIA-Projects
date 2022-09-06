#include <stdint.h>
#include "vga.h"

static volatile uint16_t * const fb = (uint16_t *)VGA_FB_ADDR;

// Write a character using true VGA text mode programming (emulated by the hypevisor)
void putchar_emul(int x, int y, char ch, color_t fg, color_t bg) {
	int offset = y * VGA_XRES + x;
	if (offset < VGA_XRES * VGA_YRES)
		fb[offset] = (uint8_t)ch | ((fg | (bg << 4)) << 8);
}