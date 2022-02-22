#ifndef VECTOR_I_TRIANGLE_H
#define VECTOR_I_TRIANGLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"

#define VECTOR_I_TRIANGLE_INIT_CAPACITY 4

typedef struct i_triangle{
    int p1, p2, p3;
    } i_triangle;

typedef struct vector_i_triangle {
    i_triangle *content; // actual content of the vector_i_triangle
    int capacity; // capacity allocated
    int length; // actual length
} vector_i_triangle;

error_code vector_i_triangle_init(vector_i_triangle *v); // initializes an empty vector_i_triangle of site vector_i_triangle_INIT_CAPACITY size
bool vector_i_triangle_is_equal(vector_i_triangle *v1, vector_i_triangle *v2);
error_code vector_i_triangle_length(vector_i_triangle *v, int *length); // stores the length of v in length
error_code vector_i_triangle_push(vector_i_triangle *v, i_triangle element); // push an element
error_code vector_i_triangle_pop(vector_i_triangle *v, i_triangle *element); // pop the last element
error_code vector_i_triangle_set(vector_i_triangle *v, int index, i_triangle element); // set index-th element
error_code vector_i_triangle_get(vector_i_triangle *v, int index, i_triangle *element); // stores index-th element in *element
error_code vector_i_triangle_remove(vector_i_triangle *v, int index); // remove index-th element
error_code vector_i_triangle_insert(vector_i_triangle *v, i_triangle element, int index); // insert element at position index
error_code vector_i_triangle_empty(vector_i_triangle *v);
error_code vector_i_triangle_free(vector_i_triangle *v);

error_code vector_i_triangle_map(vector_i_triangle *v, i_triangle (*f)(i_triangle), vector_i_triangle *rhs); // map function f on v and stores the result in rhs
error_code vector_i_triangle_filter(vector_i_triangle *v, bool (*f)(i_triangle), vector_i_triangle *rhs); // filter v with predicate f and stores the result in rhs

void vector_i_triangle_print_int(vector_i_triangle *v);

error_code vector_i_triangle_default_value(vector_i_triangle *v);
error_code vector_i_triangle_resize(vector_i_triangle *v, int size);
i_triangle vector_i_triangle_get_last_element(vector_i_triangle v);
bool vector_i_triangle_is_valid(vector_i_triangle v);
bool vector_i_triangle_is_full(vector_i_triangle v);
bool vector_i_triangle_is_empty(vector_i_triangle v);

#endif
