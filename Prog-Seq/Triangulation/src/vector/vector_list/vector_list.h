#ifndef VECTOR_LIST_H
#define VECTOR_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"

typedef int type;

typedef struct element {
    type data;
    struct element* next;
} element;

//typedef element* lst_vector;

typedef struct lst_vector {
    int length;
    struct element* head;
} lst_vector;

error_code lst_vector_init(lst_vector *v); // initializes an empty vector of site VECTOR_INIT_CAPACITY size
bool lst_vector_is_equal(lst_vector *v1, lst_vector *v2);
error_code lst_vector_length(lst_vector *v, int *length); // stores the length of v in length
error_code lst_vector_push(lst_vector *v, type n); // push an element
error_code lst_vector_pop(lst_vector *v, type *n); // pop the last element
error_code lst_vector_set(lst_vector *v, int index, type n); // set index-th element
error_code lst_vector_get(lst_vector *v, int index, type *n); // stores index-th element in *element
error_code lst_vector_remove(lst_vector *v, int index); // remove index-th element
error_code lst_vector_insert(lst_vector *v, type n, int index); // insert element at position index
error_code lst_vector_empty(lst_vector *v);
error_code lst_vector_free(lst_vector *v);

error_code lst_vector_map(lst_vector *v, type (*f)(type), lst_vector *rhs); // map function f on v and stores the result in rhs
error_code lst_vector_filter(lst_vector *v, bool (*f)(type), lst_vector *rhs); // filter v with predicate f and stores the result in rhs

void lst_vector_print_int(lst_vector *v);

error_code lst_vector_default_value(lst_vector *v);
error_code lst_vector_resize(lst_vector *v, int size);
type lst_vector_get_last_element(lst_vector v);
bool lst_vector_is_valid(lst_vector *v);
bool lst_vector_is_empty(lst_vector *v);

#endif
