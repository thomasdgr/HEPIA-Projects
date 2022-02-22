#ifndef VECTOR_LIST_I_EDGE_H
#define VECTOR_LIST_I_EDGE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../../error/error.h"
#include "../vector/vector_i_edge.h"

typedef struct element_i_edge {
    i_edge data;
    struct element_i_edge* next;
} element_i_edge;

//typedef element_i_edge* lst_vector_i_edge;

typedef struct lst_vector_i_edge {
    int length;
    struct element_i_edge* head;
} lst_vector_i_edge;

error_code lst_vector_i_edge_init(lst_vector_i_edge *v); // initializes an empty vector of site VECTOR_INIT_CAPACITY size
bool lst_vector_i_edge_is_equal(lst_vector_i_edge *v1, lst_vector_i_edge *v2);
error_code lst_vector_i_edge_length(lst_vector_i_edge *v, int *length); // stores the length of v in length
error_code lst_vector_i_edge_push(lst_vector_i_edge *v, i_edge n); // push an i_edge
error_code lst_vector_i_edge_pop(lst_vector_i_edge *v, i_edge *n); // pop the last i_edge
error_code lst_vector_i_edge_set(lst_vector_i_edge *v, int index, i_edge n); // set index-th i_edge
error_code lst_vector_i_edge_get(lst_vector_i_edge *v, int index, i_edge *n); // stores index-th i_edge in *i_edge
error_code lst_vector_i_edge_remove(lst_vector_i_edge *v, int index); // remove index-th i_edge
error_code lst_vector_i_edge_insert(lst_vector_i_edge *v, i_edge n, int index); // insert i_edge at position index
error_code lst_vector_i_edge_empty(lst_vector_i_edge *v);
error_code lst_vector_i_edge_free(lst_vector_i_edge *v);

error_code lst_vector_i_edge_map(lst_vector_i_edge *v, i_edge (*f)(i_edge), lst_vector_i_edge *rhs); // map function f on v and stores the result in rhs
error_code lst_vector_i_edge_filter(lst_vector_i_edge *v, bool (*f)(i_edge), lst_vector_i_edge *rhs); // filter v with predicate f and stores the result in rhs

void lst_vector_i_edge_print_int(lst_vector_i_edge *v);

error_code lst_vector_i_edge_default_value(lst_vector_i_edge *v);
error_code lst_vector_i_edge_resize(lst_vector_i_edge *v, int size);
i_edge lst_vector_i_edge_get_last_element(lst_vector_i_edge v);
bool lst_vector_i_edge_is_valid(lst_vector_i_edge *v);
bool lst_vector_i_edge_is_empty(lst_vector_i_edge *v);

#endif
