#ifndef _FONT_H_
#define _FONT_H_

#include <stdint.h>

#define FONT_HEIGHT      16
#define FONT_WIDTH        8
#define CHARS_COUNT     256

extern uint8_t font_8x16[CHARS_COUNT*FONT_HEIGHT];

#endif
