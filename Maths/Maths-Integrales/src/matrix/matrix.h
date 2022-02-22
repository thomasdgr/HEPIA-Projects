#ifndef MATRIX_H
#define MATRIX_H

// rajouté
#define _GNU_SOURCE
#define M_PI 3.14159265358979323846

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct matrix {
    int m, n;
    double** data;
} matrix;

// rajouté
bool matrix_is_valide(matrix mat);
matrix matrix_default_value(matrix mat);
matrix transfert_clone_to_final(matrix mat_clone, matrix mat_final);

matrix matrix_create(int m, int n);

void matrix_destroy(matrix *mat);

matrix matrix_create_from_array(int m, int n, double data[]);

matrix matrix_clone(matrix mat);

void matrix_print(matrix mat);

int matrix_resize(matrix *mat, int m, int n);

bool matrix_is_approx_equal(matrix mat1, matrix mat2, double epsilon);

bool matrix_is_equal(matrix mat1, matrix mat2);

int matrix_add_in_place(matrix mat1, matrix mat2);

int matrix_sub_in_place(matrix mat1, matrix mat2);

int matrix_mult_in_place(matrix *mat1, matrix mat2);

int matrix_add_scalar_in_place(matrix mat1, double n);

int matrix_mult_scalar_in_place(matrix mat1, double n);

int matrix_transpose_in_place(matrix *mat);

int matrix_normalize_in_place(matrix mat);

int matrix_clipper_in_place(matrix mat);

int matrix_convolve_in_place(matrix *mat, matrix kernel);

matrix matrix_add(matrix mat1, matrix mat2);

matrix matrix_sub(matrix mat1, matrix mat2);

matrix matrix_mult(matrix mat1, matrix mat2);

matrix matrix_add_scalar(matrix mat, double n);

matrix matrix_mult_scalar(matrix mat, double n);

matrix matrix_transpose(matrix mat);

matrix matrix_normalize(matrix mat);

matrix matrix_clipper(matrix mat);

matrix matrix_convolve(matrix mat, matrix kernel);

matrix matrix_crop(matrix mat, int size);

double matrix_max_value(matrix mat);

double matrix_min_value(matrix mat);

void matrix_convert_in_eight_bits_in_place(matrix mat);

#endif