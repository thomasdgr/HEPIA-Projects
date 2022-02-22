#ifndef PGM_H_
#define PGM_H_

#include "matrix.h"

typedef struct pgm{
    int max;
    matrix mat;
} pgm;

pgm pgm_read(char *filename);

void pgm_destroy(pgm *image);

int pgm_write(char *filename, pgm image);

bool pgm_is_equal(pgm i1, pgm i2);

bool pgm_is_approx_equal(pgm i1, pgm i2, double epsilon);

#endif