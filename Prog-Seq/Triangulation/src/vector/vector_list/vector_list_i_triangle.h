#ifndef VECTOR_LIST_I_TRIANGLE_H
#define VECTOR_LIST_I_TRIANGLE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"
#include "../vector/vector_i_triangle.h"

typedef struct element_i_triangle {
    i_triangle data;
    struct element_i_triangle* next;
} element_i_triangle;

//typedef element_i_triangle* lst_vector_i_triangle;

typedef struct lst_vector_i_triangle {
    int length;
    struct element_i_triangle* head;
} lst_vector_i_triangle;

error_code lst_vector_i_triangle_init(lst_vector_i_triangle *v); // initializes an empty vector of site VECTOR_INIT_CAPACITY size
bool lst_vector_i_triangle_is_equal(lst_vector_i_triangle *v1, lst_vector_i_triangle *v2);
error_code lst_vector_i_triangle_length(lst_vector_i_triangle *v, int *length); // stores the length of v in length
error_code lst_vector_i_triangle_push(lst_vector_i_triangle *v, i_triangle n); // push an element_i_triangle
error_code lst_vector_i_triangle_pop(lst_vector_i_triangle *v, i_triangle *n); // pop the last element_i_triangle
error_code lst_vector_i_triangle_set(lst_vector_i_triangle *v, int index, i_triangle n); // set index-th element_i_triangle
error_code lst_vector_i_triangle_get(lst_vector_i_triangle *v, int index, i_triangle *n); // stores index-th element_i_triangle in *element_i_triangle
error_code lst_vector_i_triangle_remove(lst_vector_i_triangle *v, int index); // remove index-th element_i_triangle
error_code lst_vector_i_triangle_insert(lst_vector_i_triangle *v, i_triangle n, int index); // insert element_i_triangle at position index
error_code lst_vector_i_triangle_empty(lst_vector_i_triangle *v);
error_code lst_vector_i_triangle_free(lst_vector_i_triangle *v);

error_code lst_vector_i_triangle_map(lst_vector_i_triangle *v, i_triangle (*f)(i_triangle), lst_vector_i_triangle *rhs); // map function f on v and stores the result in rhs
error_code lst_vector_i_triangle_filter(lst_vector_i_triangle *v, bool (*f)(i_triangle), lst_vector_i_triangle *rhs); // filter v with predicate f and stores the result in rhs

void lst_vector_i_triangle_print_int(lst_vector_i_triangle *v);

error_code lst_vector_i_triangle_default_value(lst_vector_i_triangle *v);
error_code lst_vector_i_triangle_resize(lst_vector_i_triangle *v, int size);
i_triangle lst_vector_i_triangle_get_last_element(lst_vector_i_triangle v);
bool lst_vector_i_triangle_is_valid(lst_vector_i_triangle *v);
bool lst_vector_i_triangle_is_empty(lst_vector_i_triangle *v);

#endif
