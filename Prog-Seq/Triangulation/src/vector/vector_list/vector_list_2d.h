#ifndef VECTOR_LIST_2D_H
#define VECTOR_LIST_2D_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"
#include "../vector/vector_2d.h"

typedef struct element_2d {
    point_2d data;
    struct element_2d* next;
} element_2d;

//typedef element_2d* lst_vector_2d;

typedef struct lst_vector_2d {
    int length;
    struct element_2d* head;
} lst_vector_2d;

error_code lst_vector_2d_init(lst_vector_2d *v); // initializes an empty vector of site VECTOR_INIT_CAPACITY size
bool lst_vector_2d_is_equal(lst_vector_2d *v1, lst_vector_2d *v2);
error_code lst_vector_2d_length(lst_vector_2d *v, int *length); // stores the length of v in length
error_code lst_vector_2d_push(lst_vector_2d *v, point_2d n); // push an element_2d
error_code lst_vector_2d_pop(lst_vector_2d *v, point_2d *n); // pop the last element_2d
error_code lst_vector_2d_set(lst_vector_2d *v, int index, point_2d n); // set index-th element_2d
error_code lst_vector_2d_get(lst_vector_2d *v, int index, point_2d *n); // stores index-th element_2d in *element_2d
error_code lst_vector_2d_remove(lst_vector_2d *v, int index); // remove index-th element_2d
error_code lst_vector_2d_insert(lst_vector_2d *v, point_2d n, int index); // insert element_2d at position index
error_code lst_vector_2d_empty(lst_vector_2d *v);
error_code lst_vector_2d_free(lst_vector_2d *v);

error_code lst_vector_2d_map(lst_vector_2d *v, point_2d (*f)(point_2d), lst_vector_2d *rhs); // map function f on v and stores the result in rhs
error_code lst_vector_2d_filter(lst_vector_2d *v, bool (*f)(point_2d), lst_vector_2d *rhs); // filter v with predicate f and stores the result in rhs

void lst_vector_2d_print_int(lst_vector_2d *v);

error_code lst_vector_2d_default_value(lst_vector_2d *v);
error_code lst_vector_2d_resize(lst_vector_2d *v, int size);
point_2d lst_vector_2d_get_last_element(lst_vector_2d v);
bool lst_vector_2d_is_valid(lst_vector_2d *v);
bool lst_vector_2d_is_empty(lst_vector_2d *v);

#endif
