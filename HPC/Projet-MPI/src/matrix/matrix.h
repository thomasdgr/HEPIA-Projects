#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <mpi.h>

typedef struct matrix {
    int m, n;
    double** data;
} matrix;

typedef struct vector {
    double *content;
    int capacity;
    int length;
} vector;

matrix init_tab(int m, int n);
void free_tab(matrix* U);
void copy_tab(matrix* U1, matrix U2);
void print_tab(matrix U);
matrix init_file(char* filename);
matrix read_file(char* filename);
void write_file(char *filename, matrix mat);
void apply_laplace(matrix* mat, double* bufRecv1, double* bufRecv2);
int* compute_lines(int m, int n, int nProc);
int* compute_displacement(int rank, int nProc, int* nbLines, int size);
void update_lines(int* nbLines, int nProc, int size);
void update_displacement(int* displacement, int* nbLines, int nProc, int rank);
double* get_line(matrix mat, int index);
double* get_missing_line(matrix mat, int index, int voisin1, int voisin2, int tag1, int tag2);
void vector_push(vector *v, double element);

#endif