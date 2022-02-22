#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>

void get_image_file_size(const char *bmp_filename, int *im_width, int *im_height);

SDL_Texture *create_texture_from_image_file(SDL_Renderer *renderer, const char *img_filename, SDL_Rect *img_rect);

void wait_key_release();

struct timespec wait_until(struct timespec time_start, unsigned long offset_ms);

#endif
