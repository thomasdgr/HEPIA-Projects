#ifndef DECODE_H
#define DECODE_H

#include "matrix.h"

void factorisation(matrix *L, matrix *U);
matrix create_under_matrix(matrix mat, int esquive_i, int esquive_j);
double determinant(matrix mat);

matrix resolve_z(matrix M, matrix B);
matrix resolve_x(matrix M, matrix Z);
double testT(double nb);

#endif