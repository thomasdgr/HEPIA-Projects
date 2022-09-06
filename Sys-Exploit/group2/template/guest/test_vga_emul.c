#include <stdint.h>
#include "vga.h"

void test_vga_emul() {
    uint8_t *screen = (uint8_t *)VGA_FB_ADDR;
    uint8_t *p, *q;
    char *m;

    for (int i = 0; i < 80; i++) {
        p = screen+VGA_FB_PITCH*7+i*2;
        p[0] = 33+i;

        p = screen+VGA_FB_PITCH*21+i*2;
        p[1] = 7|(4 << 4);
    }

    p = screen;
    m = "Light_Red";
    while (*m) {
        p[0] = *m;
        p[1] = (COL_DARK_GREY << 4) | COL_LIGHT_RED;
        p += 2;
        m++;
    }

    p = screen+VGA_FB_PITCH-2;
    p[0] = 'X';
    p[1] = (COL_GREEN << 4) | COL_LIGHT_MAGENTA;

    p = screen+VGA_FB_PITCH*(VGA_YRES-1);
    p[0] = 2;  // solid smiley
    p[1] = (COL_BROWN << 4) | COL_LIGHT_GREEN;

    // color test in the center of the screen
    p = screen+VGA_FB_PITCH*9+66;
    q = p+VGA_FB_PITCH;
    m = "\1\2MULTICOLORS!!";
    uint8_t color = 1;
    while (*m) {
        p[0] = *m;
        p[1] = color;
        p += 2;
        q[0] = *m;
        q[1] = color << 4;
        q += 2;
        color = (color+1) % _COL_END_;
        m++;
    }

    // Display the whole character set at the bottom of the screen
    p = screen+VGA_FB_PITCH*15;
    for (int i = 0; i < 256; i++) {
        p[0] = i;
        p[1] = COL_YELLOW | (COL_LIGHT_BLUE << 4);
        p += 2;
    }

    p = screen+VGA_FB_PITCH*(VGA_YRES-1)+VGA_FB_PITCH-2;
    p[0] = 1;  // smiley
    p[1] = (COL_CYAN << 4) | COL_WHITE;

    // 16-bit write
    // col 40, line 4: dark pink B on dark grey background
    uint16_t *pB = (uint16_t*)(VGA_FB_ADDR+VGA_FB_PITCH*4+VGA_FB_PITCH/2);
    uint8_t colB = COL_MAGENTA | (COL_LIGHT_GREY << 4);
    pB[0] = 'B' | (colB << 8);

    // 32-bit write
    // col 40-41, line 5: light cyan C on red background + light red D on dark green background
    uint32_t *pCD = (uint32_t*)(VGA_FB_ADDR+VGA_FB_PITCH*5+VGA_FB_PITCH/2);
    uint8_t colC = COL_LIGHT_CYAN | (COL_RED << 4);
    uint8_t colD = COL_LIGHT_RED | (COL_GREEN << 4);
    pCD[0] = 'C' | (colC << 8) | ('D' << 16) | (colD << 24);

    for (int i = 0; i < 80; i++) {
        p = screen+VGA_FB_PITCH*7+i*2;
        p[1] = 10|(5 << 4);

        p = screen+VGA_FB_PITCH*21+i*2;
        p[0] = 33+i+80;
    }
}

void guest_main() {
    test_vga_emul();
	while(1);
}