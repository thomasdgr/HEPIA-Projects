#ifndef FILTER_H
#define FILTER_H

#include "matrix.h"
// démo :
//int filter_high_pass_in_place(matrix *mat);
//matrix filter_high_pass(matrix mat);

int apply_filter_in_place(matrix *mat, double array[], int kernel_m, int kernel_n);

int filter_sharpen_in_place(matrix *mat);

int filter_blur_in_place(matrix *mat);

int filter_edge_enhance_in_place(matrix *mat);

int filter_edge_detect_in_place(matrix *mat);

int filter_emboss_in_place(matrix *mat);

int filter_sobel_in_place(matrix *mat);

int filter_smooth_in_place(matrix *mat);

matrix filter_sharpen(matrix mat);

matrix filter_blur(matrix mat);

matrix filter_edge_enhance(matrix mat);

matrix filter_edge_detect(matrix mat);

matrix filter_emboss(matrix mat);

matrix filter_sobel(matrix mat);

matrix filter_smooth(matrix mat);

#endif
