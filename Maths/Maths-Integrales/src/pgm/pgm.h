#ifndef PGM_H_
#define PGM_H_

#include "../matrix/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct pgm{
    int max;
    matrix mat;
} pgm;

pgm pgm_read(char *filename);

uint16_t invertEndian(uint16_t val);

pgm pgm_clone(pgm image);

pgm pgm_crop(pgm image, int to_crop);

pgm pgm_convolve(pgm image, matrix kernel);

void pgm_destroy(pgm *image);

int pgm_write(char *filename, pgm image);

bool pgm_is_equal(pgm i1, pgm i2);

bool pgm_is_approx_equal(pgm i1, pgm i2, double epsilon);

matrix applyConvolveOnPGM(pgm read, double ker[]);

#endif
