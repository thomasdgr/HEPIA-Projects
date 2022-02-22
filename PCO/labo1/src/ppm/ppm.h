#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Store a pixel with 8-bit per component
typedef struct pixel_st {
	uint8_t r, g, b;   // Red, green, blue components of the pixel
} pixel_t;

// Store a 24-bit per pixel image: dimension and pixel data
typedef struct img_st {
	int width;
	int height;
	pixel_t *data;  // Pixel data
} img_t;

extern img_t *alloc_img(int width, int height);
extern void free_img(img_t *img);
extern img_t *load_ppm(char *filename);
extern bool write_ppm(char *filename, img_t *img);
img_t *img_t_clone(img_t *img);

