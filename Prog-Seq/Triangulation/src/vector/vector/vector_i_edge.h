#ifndef VECTOR_I_EDGE_H
#define VECTOR_I_EDGE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"

#define VECTOR_I_EDGE_INIT_CAPACITY 4

typedef struct i_edge {
    int p1, p2;
    } i_edge;

typedef struct vector_i_edge {
    i_edge *content; // actual content of the vector_i_edge
    int capacity; // capacity allocated
    int length; // actual length
} vector_i_edge;

error_code vector_i_edge_init(vector_i_edge *v); // initializes an empty vector_i_edge of site vector_i_edge_INIT_CAPACITY size
bool vector_i_edge_is_equal(vector_i_edge *v1, vector_i_edge *v2);
error_code vector_i_edge_length(vector_i_edge *v, int *length); // stores the length of v in length
error_code vector_i_edge_push(vector_i_edge *v, i_edge element); // push an element
error_code vector_i_edge_pop(vector_i_edge *v, i_edge *element); // pop the last element
error_code vector_i_edge_set(vector_i_edge *v, int index, i_edge element); // set index-th element
error_code vector_i_edge_get(vector_i_edge *v, int index, i_edge *element); // stores index-th element in *element
error_code vector_i_edge_remove(vector_i_edge *v, int index); // remove index-th element
error_code vector_i_edge_insert(vector_i_edge *v, i_edge element, int index); // insert element at position index
error_code vector_i_edge_empty(vector_i_edge *v);
error_code vector_i_edge_free(vector_i_edge *v);

error_code vector_i_edge_map(vector_i_edge *v, i_edge (*f)(i_edge), vector_i_edge *rhs); // map function f on v and stores the result in rhs
error_code vector_i_edge_filter(vector_i_edge *v, bool (*f)(i_edge), vector_i_edge *rhs); // filter v with predicate f and stores the result in rhs

void vector_i_edge_print_int(vector_i_edge *v);

error_code vector_i_edge_default_value(vector_i_edge *v);
error_code vector_i_edge_resize(vector_i_edge *v, int size);
i_edge vector_i_edge_get_last_element(vector_i_edge v);
bool vector_i_edge_is_valid(vector_i_edge v);
bool vector_i_edge_is_full(vector_i_edge v);
bool vector_i_edge_is_empty(vector_i_edge v);

#endif
