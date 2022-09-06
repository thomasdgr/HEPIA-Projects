/**
* @file vga_vmm.c
* @brief vga management
*
* Manage vmm usage with emulation and functions to display the 
* framebuffer content on a SDL window
*
* @author Rod Quentin, Dagier Thomas
* @bug No known bugs.
* @date 02.04.2022
* @version 1.0
*/

#include "vga_vmm.h"

// array of color used to know how to display the char
// and the background color on the SDL window
// (colors picked from the image given in /resources)
uint32_t vga_color_array[16] = {
    MAKE_COLOR(0,0,0),
    MAKE_COLOR(0,14,163),
    MAKE_COLOR(0,169,46),
    MAKE_COLOR(0,169,167),
    MAKE_COLOR(185,0,25),
    MAKE_COLOR(184,0,164),
    MAKE_COLOR(182,84,33),
    MAKE_COLOR(169,169,169),
    MAKE_COLOR(86,86,86),
    MAKE_COLOR(83,88,247),
    MAKE_COLOR(0,255,105),
    MAKE_COLOR(0,255, 253),
    MAKE_COLOR(255,82,91),
    MAKE_COLOR(255,85,249),
    MAKE_COLOR(255,254,110),
    MAKE_COLOR(255,255,255)
};

/**
* put a char in a SDL context
* @param ctxt the current SDL context
* @param c the char to put in the SDL context
* @param x the x coord of the char in the SDL context
* @param y the y coord of the char in the SDL context
* @param bg_color the color of the char's background
* @param char_color the color of the char
*/
void vga_ctxt_putchar(struct gfx_context_t *ctxt, char c, int x, int y, uint8_t bg_color, uint8_t char_color){
    for(int i = 0; i < FONT_HEIGHT; i++){
        for(int j = 0; j < FONT_WIDTH; j++){
            uint8_t line = (font_8x16[((uint8_t)c * FONT_HEIGHT) + i]);
            bool is_text = (line >> (FONT_WIDTH -1 - j)) & 0b1;
            uint32_t color = is_text ? vga_color_array[char_color] : vga_color_array[bg_color];
            gfx_putpixel(ctxt,  x + j, y + i, color);
        }
    }
}

/**
* display the SDL context with the framebuffer content
* @param ctxt the current SDL context
* @param vga_buf the framebuffer to render
*/
void vga_render(struct gfx_context_t *ctxt, vga_char* vga_buf){
    for(int i = 0; i < FB_YRES; i++){
        for(int j = 0; j < FB_XRES; j++){
            vga_char vga_c = vga_buf[i*FB_XRES + j];
            vga_ctxt_putchar(ctxt, vga_c.ascii_char, j * FONT_WIDTH, i * FONT_HEIGHT, vga_c.bg_color, vga_c.char_color);
       }
    }
}

/**
* called in a thread to emulates VGA display with refresh rate of 60Hz. 
* @param p the framebuffer to display
*/
void* vga_thread_display(void* p){
    vga_char* char_buff = (vga_char*)p;
    struct gfx_context_t *ctxt = gfx_create("window", FB_XRES*FONT_WIDTH, FB_YRES*FONT_HEIGHT);
	if (!ctxt) {
		fprintf(stderr, "Graphics initialization failed!\n");
		return NULL;
	}
    struct timespec t_request, t_remain;
    t_request.tv_sec = 0;
    // period in ns of 60Hz : (1/60) * 10^9
    t_request.tv_nsec = 1000000000 / VGA_FREQ_HZ ;
    while(gfx_keypressed() != SDLK_ESCAPE){
		vga_render(ctxt, char_buff);
		gfx_present(ctxt);
        // sleep function pauses the thread
        nanosleep(&t_request, &t_remain);
	}
    gfx_destroy(ctxt);
    return NULL;
}