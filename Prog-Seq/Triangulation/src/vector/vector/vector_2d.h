#ifndef VECTOR_2D_H
#define VECTOR_2D_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"

#define VECTOR_2D_INIT_CAPACITY 4

typedef struct point_2d{
    double x, y;
    } point_2d;

typedef struct vector_2d {
    point_2d *content; // actual content of the vector
    int capacity; // capacity allocated
    int length; // actual length
} vector_2d;

error_code vector_2d_init(vector_2d *v); // initializes an empty vector_2d of site VECTOR_2D_INIT_CAPACITY size
bool vector_2d_is_equal(vector_2d *v1, vector_2d *v2);
error_code vector_2d_length(vector_2d *v, int *length); // stores the length of v in length
error_code vector_2d_push(vector_2d *v, point_2d element); // push an element
error_code vector_2d_pop(vector_2d *v, point_2d *element); // pop the last element
error_code vector_2d_set(vector_2d *v, int index, point_2d element); // set index-th element
error_code vector_2d_get(vector_2d *v, int index, point_2d *element); // stores index-th element in *element
error_code vector_2d_remove(vector_2d *v, int index); // remove index-th element
error_code vector_2d_insert(vector_2d *v, point_2d element, int index); // insert element at position index
error_code vector_2d_empty(vector_2d *v);
error_code vector_2d_free(vector_2d *v);

error_code vector_2d_map(vector_2d *v, point_2d (*f)(point_2d), vector_2d *rhs); // map function f on v and stores the result in rhs
error_code vector_2d_filter(vector_2d *v, bool (*f)(point_2d), vector_2d *rhs); // filter v with predicate f and stores the result in rhs

void vector_2d_print_int(vector_2d *v);

error_code vector_2d_default_value(vector_2d *v);
error_code vector_2d_resize(vector_2d *v, int size);
point_2d vector_2d_get_last_element(vector_2d v);
bool vector_2d_is_valid(vector_2d v);
bool vector_2d_is_full(vector_2d v);
bool vector_2d_is_empty(vector_2d v);

#endif
