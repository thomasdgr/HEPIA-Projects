#ifndef _VGA_VMM_H_
#define _VGA_VMM_H_

#include "gfx.h"
#include "font.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define FB_XRES  80
#define FB_YRES  25
#define FB_SIZE (FB_YRES * FB_XRES) // the number of element in the framebuffer
#define VGA_FREQ_HZ 60 // the current frequency to refresh the SDL window

// struct of the data stored in the framebuffer
typedef struct _vga_char{
    uint8_t ascii_char; // the value of the char
    uint8_t bg_color;   // the color of the char's background
    uint8_t char_color; // the color of the char
} vga_char;

void vga_ctxt_putchar(struct gfx_context_t *ctxt, char c, int x, int y, uint8_t bg_color, uint8_t char_color);
void vga_render(struct gfx_context_t *ctxt, vga_char* vga_buf);
void* vga_thread_display(void* p);

#endif