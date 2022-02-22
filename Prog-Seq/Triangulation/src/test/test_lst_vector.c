#include "test_lst_vector.h"
#include "../vector/vector_list/vector_list.h"
#include "../vector/map_functions.h"
#include "../vector/filter_functions.h"
#include "stdlib.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"

// les CU_ASSERT passent mais pour l'afichage des tests c'est plus simple
//de ne pas les faire planter volontairement

void test_lst_vector_init(){
    lst_vector v;
    CU_ASSERT(lst_vector_init(&v) == ok);
    CU_ASSERT(v.head == NULL);
}

void test_lst_vector_is_equal(){
    lst_vector v1, v2;
    lst_vector_init(&v1);
    lst_vector_init(&v2);

    CU_ASSERT(lst_vector_is_equal(&v1, &v2));

    lst_vector_push(&v1, 1);
    lst_vector_push(&v1, 2);
    lst_vector_push(&v1, 3);

    lst_vector_push(&v2, 1);
    lst_vector_push(&v2, 2);
    lst_vector_push(&v2, 3);

    CU_ASSERT(lst_vector_is_equal(&v1, &v2));
    if(v1.head != NULL) lst_vector_set(&v1, 0, 2);
    CU_ASSERT(!lst_vector_is_equal(&v1, &v2));
    if(v1.head != NULL) lst_vector_set(&v1, 0, 3);
    CU_ASSERT(lst_vector_is_equal(&v1, &v2));
    lst_vector_push(&v1, 3);
    CU_ASSERT(!lst_vector_is_equal(&v1, &v2));
    lst_vector_free(&v1);
    lst_vector_free(&v2);
}

void test_lst_vector_length(){
    lst_vector v;
    lst_vector_init(&v);
    int length;

    CU_ASSERT(lst_vector_length(&v, &length) == ok);
    CU_ASSERT(length == 0);

    lst_vector_push(&v, 1);
    lst_vector_push(&v, 1);
    lst_vector_push(&v, 1);

    CU_ASSERT(lst_vector_length(&v, &length) == ok);
    CU_ASSERT(length == 3);
    lst_vector_free(&v);
}

void test_lst_vector_push(){
    lst_vector v1, v2;
    lst_vector_init(&v1);
    lst_vector_init(&v2);

    lst_vector_push(&v1, 1);
    lst_vector_push(&v1, 2);
    lst_vector_push(&v1, 3);
    lst_vector_push(&v1, 4);

    CU_ASSERT(lst_vector_push(&v2, 1) == ok);
    CU_ASSERT(lst_vector_push(&v2, 2) == ok);
    CU_ASSERT(lst_vector_push(&v2, 3) == ok);
    CU_ASSERT(lst_vector_push(&v2, 4) == ok);

    CU_ASSERT(lst_vector_is_equal(&v1, &v2));
    lst_vector_free(&v1);
    lst_vector_free(&v2);
}

void test_lst_vector_pop(){
    lst_vector v;
    lst_vector_init(&v);
    type element;

    //CU_ASSERT(lst_vector_pop(&v, &element) == out_of_bounds);

    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    CU_ASSERT(lst_vector_pop(&v, &element) == ok);
    CU_ASSERT(element == 11);
    CU_ASSERT(lst_vector_pop(&v, &element) == ok);
    CU_ASSERT(element == 14);
    CU_ASSERT(lst_vector_pop(&v, &element) == ok);
    CU_ASSERT(element == 51);
    lst_vector_free(&v);
}

void test_lst_vector_set(){
    lst_vector v;
    lst_vector_init(&v);
    type element;

    //CU_ASSERT(lst_vector_pop(&v, &element) == out_of_bounds);

    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);
    CU_ASSERT(lst_vector_set(&v, 0, 82) == ok);
    CU_ASSERT(lst_vector_set(&v, 2, 42) == ok);
    CU_ASSERT(lst_vector_pop(&v, &element) == ok);
    CU_ASSERT(element == 82);
    CU_ASSERT(lst_vector_pop(&v, &element) == ok);
    CU_ASSERT(element == 14);
    CU_ASSERT(lst_vector_pop(&v, &element) == ok);
    CU_ASSERT(element == 42);
    lst_vector_free(&v);
}

void test_lst_vector_get(){
    lst_vector v;
    lst_vector_init(&v);
    type element;

    //CU_ASSERT(lst_vector_pop(&v, &element) == out_of_bounds);

    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    CU_ASSERT(lst_vector_get(&v, 2, &element) == ok);
    CU_ASSERT(element == 51);
    CU_ASSERT(lst_vector_get(&v, 1, &element) == ok);
    CU_ASSERT(element == 14);
    CU_ASSERT(lst_vector_get(&v, 0, &element) == ok);
    CU_ASSERT(element == 11);
    CU_ASSERT(lst_vector_pop(&v, &element) == ok);
    CU_ASSERT(element == 11);

    lst_vector_free(&v);
}

void test_lst_vector_remove(){
    lst_vector v;
    lst_vector_init(&v);
    type element;

    //CU_ASSERT(lst_vector_pop(&v, &element) == out_of_bounds);

    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    CU_ASSERT(lst_vector_get(&v, 2, &element) == ok);
    CU_ASSERT(element == 51);
    CU_ASSERT(lst_vector_remove(&v, 0) == ok);
    CU_ASSERT(lst_vector_get(&v, 1, &element) == ok);
    CU_ASSERT(element == 51);
    lst_vector_push(&v, 51);
    CU_ASSERT(lst_vector_set(&v, 2, 64) == ok);
    CU_ASSERT(lst_vector_remove(&v, 1) == ok);
    CU_ASSERT(lst_vector_get(&v, 1, &element) == ok);
    CU_ASSERT(element == 64);
    lst_vector_free(&v);
}

void test_lst_vector_insert(){
    lst_vector v;
    lst_vector_init(&v);
    type element;

    //CU_ASSERT(lst_vector_pop(&v, &element) == out_of_bounds);

    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    CU_ASSERT(lst_vector_get(&v, 2, &element) == ok);
    CU_ASSERT(element == 51);
    CU_ASSERT(lst_vector_insert(&v, 70, 1) == ok);
    CU_ASSERT(lst_vector_get(&v, 1, &element) == ok);
    CU_ASSERT(element == 70);
    CU_ASSERT(lst_vector_get(&v, 2, &element) == ok);
    CU_ASSERT(element == 14);

    lst_vector_free(&v);
}

void test_lst_vector_empty(){
    lst_vector v;
    lst_vector_init(&v);
    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    lst_vector_empty(&v);
    CU_ASSERT(v.head == NULL);
}

void test_lst_vector_free(){
    lst_vector v;
    lst_vector_init(&v);
    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    lst_vector_free(&v);
    CU_ASSERT(v.head == NULL);
}

void test_lst_vector_map(){
    lst_vector v, v2;
    type element;
    lst_vector_init(&v);
    lst_vector_init(&v2);
    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    CU_ASSERT(lst_vector_map(&v, square, &v2) == ok);
    CU_ASSERT(lst_vector_get(&v2, 0, &element) == ok);
    CU_ASSERT(element == 121);
    CU_ASSERT(lst_vector_get(&v2, 1, &element) == ok);
    CU_ASSERT(element == 196);
    CU_ASSERT(lst_vector_get(&v2, 2, &element) == ok);
    CU_ASSERT(element == 2601);

    lst_vector_free(&v);
    lst_vector_free(&v2);
}

void test_lst_vector_filter(){
    lst_vector v, v2;
    type element;
    int length;

    lst_vector_init(&v);
    lst_vector_init(&v2);
    lst_vector_push(&v, 51);
    lst_vector_push(&v, 14);
    lst_vector_push(&v, 11);

    CU_ASSERT(lst_vector_filter(&v, is_even, &v2) == ok);
    CU_ASSERT(lst_vector_get(&v2, 0, &element) == ok);
    CU_ASSERT(element == 14);
    CU_ASSERT(lst_vector_length(&v2, &length) == ok);
    CU_ASSERT(length == 1);

    lst_vector_free(&v);
    lst_vector_free(&v2);
}
