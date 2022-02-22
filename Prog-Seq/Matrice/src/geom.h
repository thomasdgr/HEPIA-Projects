#ifndef GEOM_H
#define GEOM_H

#include "matrix.h"

int geom_vertical_axis_reflect_in_place(matrix *mat);

int geom_horizontal_axis_reflect_in_place(matrix *mat);

int geom_central_reflect_in_place(matrix *mat);

int geom_rotate_in_place(matrix *mat, double angle, matrix center);

int geom_photomaton_in_place(matrix *mat);

int geom_translate_in_place(matrix *mat, matrix translation);

int geom_zoom_in_place(matrix *mat, matrix factors);

matrix geom_vertical_axis_reflect(matrix mat);

matrix geom_horizontal_axis_reflect(matrix mat);

matrix geom_central_reflect(matrix mat);

matrix geom_rotate(matrix mat, double angle, matrix center);

matrix geom_photomaton(matrix mat);

matrix geom_translate(matrix mat, matrix translation);

matrix geom_zoom(matrix mat, matrix factors);

#endif