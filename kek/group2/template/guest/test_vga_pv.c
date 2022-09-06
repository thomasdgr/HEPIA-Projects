#include <stdint.h>
#include "vga.h"

void test_vga_pv() {
    int x, y;
    char *m;

    x = 0;
    y = 0;
    m = "Light_Red";
    while (*m) {
        putchar_pv(x, y, *m, COL_LIGHT_RED, COL_DARK_GREY);
        m++;
        x++;
    }

    x = VGA_XRES-1;
    y = 0;
    putchar_pv(x, y, 'X', COL_LIGHT_MAGENTA, COL_GREEN);

    // solid smiley
    x = 0;
    y = VGA_YRES-1;
    putchar_pv(x, y, 2, COL_LIGHT_GREEN, COL_BROWN);

    // color test in the center of the screen
    x = 33;
    y = 9;
    m = "\1\2MULTICOLORS!!";
    uint8_t color = 1;
    while (*m) {
        putchar_pv(x, y, *m, color, 0);
        putchar_pv(x, y+1, *m, 0, color);
        color = (color+1) % _COL_END_;
        m++;
        x++;
    }

    // Display the whole character set at the bottom of the screen
    x = 0;
    y = 15;
    for (int i = 0; i < 256; i++) {
        putchar_pv(x, y, i, COL_YELLOW, COL_LIGHT_BLUE);
        x++;
        if (x >= VGA_XRES) {
            x = 0;
            y++;
        }
    }

    // smiley
    putchar_pv(VGA_XRES-1, VGA_YRES-1, 1, COL_WHITE, COL_CYAN);

    // col 40, line 4: dark pink B on dark grey background
    putchar_pv(40, 4, 'B', COL_MAGENTA, COL_LIGHT_GREY);

    // col 40-41, line 5: light cyan C on red background + light red D on dark green background
    putchar_pv(40, 5, 'C', COL_LIGHT_CYAN, COL_RED);
    putchar_pv(41, 5, 'D', COL_LIGHT_RED, COL_GREEN);

    for (int i = 0; i < 80; i++) {
        putchar_pv(i, 7, 33+i, 10, 5);
        putchar_pv(i, 21, 33+80+i, 7, 4);
    }
}

void guest_main() {
    test_vga_pv();
	while(1);
}