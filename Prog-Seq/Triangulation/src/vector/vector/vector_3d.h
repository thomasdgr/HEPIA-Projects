#ifndef VECTOR_3D_H
#define VECTOR_3D_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"
#include "../../lidar/lidar.h"

#define VECTOR_3D_INIT_CAPACITY 4


typedef struct vector_3d {
    point_3d *content; // actual content of the vector
    int capacity; // capacity allocated
    int length; // actual length
} vector_3d;

error_code vector_3d_init(vector_3d *v); // initializes an empty vector_3d of site vector_3d_INIT_CAPACITY size
bool vector_3d_is_equal(vector_3d *v1, vector_3d *v2);
error_code vector_3d_length(vector_3d *v, int *length); // stores the length of v in length
error_code vector_3d_push(vector_3d *v, point_3d element); // push an element
error_code vector_3d_pop(vector_3d *v, point_3d *element); // pop the last element
error_code vector_3d_set(vector_3d *v, int index, point_3d element); // set index-th element
error_code vector_3d_get(vector_3d *v, int index, point_3d *element); // stores index-th element in *element
error_code vector_3d_remove(vector_3d *v, int index); // remove index-th element
error_code vector_3d_insert(vector_3d *v, point_3d element, int index); // insert element at position index
error_code vector_3d_empty(vector_3d *v);
error_code vector_3d_free(vector_3d *v);

error_code vector_3d_map(vector_3d *v, point_3d (*f)(point_3d), vector_3d *rhs); // map function f on v and stores the result in rhs
error_code vector_3d_filter(vector_3d *v, bool (*f)(point_3d), vector_3d *rhs); // filter v with predicate f and stores the result in rhs

void vector_3d_print_int(vector_3d *v);

error_code vector_3d_default_value(vector_3d *v);
error_code vector_3d_resize(vector_3d *v, int size);
point_3d vector_3d_get_last_element(vector_3d v);
bool vector_3d_is_valid(vector_3d v);
bool vector_3d_is_full(vector_3d v);
bool vector_3d_is_empty(vector_3d v);

#endif
