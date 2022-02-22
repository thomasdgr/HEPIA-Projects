#ifndef VECTOR_LIST_3D_H
#define VECTOR_LIST_3D_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"
#include "../vector/vector_3d.h"

typedef struct element_3d {
    point_3d data;
    struct element_3d* next;
} element_3d;

//typedef element_3d* lst_vector_3d;

typedef struct lst_vector_3d {
    int length;
    struct element_3d* head;
} lst_vector_3d;

error_code lst_vector_3d_init(lst_vector_3d *v); // initializes an empty vector of site VECTOR_INIT_CAPACITY size
bool lst_vector_3d_is_equal(lst_vector_3d *v1, lst_vector_3d *v2);
error_code lst_vector_3d_length(lst_vector_3d *v, int* length); // stores the length of v in length
error_code lst_vector_3d_push(lst_vector_3d *v, point_3d n); // push an element_3d
error_code lst_vector_3d_pop(lst_vector_3d *v, point_3d *n); // pop the last element_3d
error_code lst_vector_3d_set(lst_vector_3d *v, int index, point_3d n); // set index-th element_3d
error_code lst_vector_3d_get(lst_vector_3d *v, int index, point_3d *n); // stores index-th element_3d in *element_3d
error_code lst_vector_3d_remove(lst_vector_3d *v, int index); // remove index-th element_3d
error_code lst_vector_3d_insert(lst_vector_3d *v, point_3d n, int index); // insert element_3d at position index
error_code lst_vector_3d_empty(lst_vector_3d *v);
error_code lst_vector_3d_free(lst_vector_3d *v);

error_code lst_vector_3d_map(lst_vector_3d *v, point_3d (*f)(point_3d), lst_vector_3d *rhs); // map function f on v and stores the result in rhs
error_code lst_vector_3d_filter(lst_vector_3d *v, bool (*f)(point_3d), lst_vector_3d *rhs); // filter v with predicate f and stores the result in rhs

void lst_vector_3d_print_int(lst_vector_3d *v);

error_code lst_vector_3d_default_value(lst_vector_3d *v);
error_code lst_vector_3d_resize(lst_vector_3d *v, int size);
point_3d lst_vector_3d_get_last_element(lst_vector_3d v);
bool lst_vector_3d_is_valid(lst_vector_3d *v);
bool lst_vector_3d_is_empty(lst_vector_3d *v);

#endif
