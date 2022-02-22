#include "test_vector.h"
#include "../vector/vector/vector.h"
#include "../vector/map_functions.h"
#include "../vector/filter_functions.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

vector create_uninitialized_vector(){
    vector v;
    v.content = NULL;
    v.length = -1;
    v.capacity = -1;
    return v;
}

void test_vector_init(){
    vector v;
    CU_ASSERT(vector_init(&v) == ok);
    CU_ASSERT(v.capacity == VECTOR_INIT_CAPACITY);
    CU_ASSERT(v.length == 0);
    CU_ASSERT(v.content != NULL);
    vector_free(&v);
}

void test_vector_is_equal(){
    vector v1 = create_uninitialized_vector();
    vector v2 = create_uninitialized_vector();
    CU_ASSERT(!vector_is_equal(&v1, &v2));
    vector_init(&v1);
    vector_init(&v2);

    vector_push(&v1, 1);
    vector_push(&v1, 2);
    vector_push(&v1, 3);

    vector_push(&v2, 1);
    vector_push(&v2, 2);
    vector_push(&v2, 3);

    v2.capacity = VECTOR_INIT_CAPACITY + 1;
    CU_ASSERT(vector_is_equal(&v1, &v2));
    if(v1.content != NULL) v1.content[0] = 2;
    CU_ASSERT(!vector_is_equal(&v1, &v2));
    if(v1.content != NULL) v1.content[0] = 1;
    v1.length = v1.length-1;
    CU_ASSERT(!vector_is_equal(&v1, &v2));
    vector_free(&v1);
    vector_free(&v2);
}

void test_vector_length(){
    vector v = create_uninitialized_vector();
    int length;
    CU_ASSERT(vector_length(&v, &length) == uninitialized);
    vector_init(&v);
    CU_ASSERT(vector_length(&v, &length) == ok);
    CU_ASSERT(length == 0);

    vector_push(&v, 1);
    vector_push(&v, 1);
    vector_push(&v, 1);

    CU_ASSERT(vector_length(&v, &length) == ok);
    CU_ASSERT(length == 3);
    vector_free(&v);
}

void test_vector_push(){
    vector v1, v2;

    v1 = create_uninitialized_vector();
    CU_ASSERT(vector_push(&v1, 1) == uninitialized);
    v1.content = malloc(4*sizeof(int));
    v1.content[0] = 1;
    v1.content[1] = 2;
    v1.content[2] = 3;
    v1.content[3] = 4;
    v1.length = 4;
    v1.capacity = 4;


    vector_init(&v2);
    CU_ASSERT(vector_push(&v2, 1) == ok);
    CU_ASSERT(vector_push(&v2, 2) == ok);
    CU_ASSERT(vector_push(&v2, 3) == ok);
    CU_ASSERT(vector_push(&v2, 4) == ok);

    CU_ASSERT(vector_is_equal(&v1, &v2));
    free(v1.content);
    vector_free(&v2);
}

void test_vector_pop(){
    vector v1, v2;
    type element;

    v1 = create_uninitialized_vector();
    CU_ASSERT(vector_pop(&v1, &element) == uninitialized)
    vector_init(&v1);
    CU_ASSERT(vector_pop(&v1, &element) == out_of_bounds);
    free(v1.content);

    v1.content = malloc(4*sizeof(int));
    v1.content[0] = 1;
    v1.content[1] = 2;
    v1.content[2] = 3;
    v1.content[3] = 4;
    v1.length = 4;
    v1.capacity = 4;

    v2.content = malloc(5*sizeof(int));
    v2.content[0] = 1;
    v2.content[1] = 2;
    v2.content[2] = 3;
    v2.content[3] = 4;
    v2.content[4] = 5;
    v2.length = 5;
    v2.capacity = 5;


    CU_ASSERT(vector_pop(&v2, &element) == ok);
    CU_ASSERT(element == 5);
    CU_ASSERT(vector_is_equal(&v1, &v2));
    free(v1.content);
    free(v2.content);
}

void test_vector_set(){
    vector v1, v2;
    vector_init(&v1);
    vector_init(&v2);
    CU_ASSERT(vector_set(&v1, -1, 1) == out_of_bounds);
    CU_ASSERT(vector_set(&v1, 1, 1) == out_of_bounds);

    vector_push(&v1, 1);
    vector_push(&v1, 1);
    vector_push(&v1, 1);

    vector_push(&v2, 1);
    vector_push(&v2, 2);
    vector_push(&v2, 1);
    CU_ASSERT(vector_set(&v1, 1, 2) == ok);

    CU_ASSERT(vector_is_equal(&v1, &v2));
    vector_free(&v1);
    vector_free(&v2);
}

void test_vector_get(){
    vector v;
    type element;
    vector_init(&v);

    vector_push(&v, 1);
    vector_push(&v, 2);
    vector_push(&v, 3);

    CU_ASSERT(vector_get(&v, 3, &element) == out_of_bounds);
    CU_ASSERT(vector_get(&v, 2, &element) == ok);
    CU_ASSERT(element == 3);
    vector_free(&v);
}

void test_vector_remove(){
    vector v1, v2;
    v1 = create_uninitialized_vector();
    CU_ASSERT(vector_remove(&v1, 0) == uninitialized);

    vector_init(&v1);
    vector_init(&v2);
    CU_ASSERT(vector_remove(&v1, 1) == out_of_bounds);

    vector_push(&v1, 1);
    vector_push(&v1, 2);
    vector_push(&v1, 3);

    vector_push(&v2, 1);
    vector_push(&v2, 3);
    CU_ASSERT(vector_remove(&v1, 1) == ok);

    CU_ASSERT(vector_is_equal(&v1, &v2));
    vector_free(&v1);
    vector_free(&v2);
}

void test_vector_insert(){
    vector v1, v2;
    v1 = create_uninitialized_vector();
    CU_ASSERT(vector_insert(&v1, 2, 2) == uninitialized);
    vector_init(&v1);
    vector_init(&v2);
    CU_ASSERT(vector_insert(&v1, 2, 2) == out_of_bounds);

    vector_push(&v1, 1);
    vector_push(&v1, 1);
    vector_push(&v1, 1);

    vector_push(&v2, 1);
    vector_push(&v2, 2);
    vector_push(&v2, 1);
    vector_push(&v2, 1);

    CU_ASSERT(vector_insert(&v1, 2, 1) == ok);

    CU_ASSERT(vector_is_equal(&v1, &v2));
    vector_free(&v1);
    vector_free(&v2);
}

void test_vector_empty(){
    vector v;
    vector_init(&v);
    vector_push(&v, 1);
    CU_ASSERT(vector_empty(&v) == ok);
    CU_ASSERT(v.length == 0);
    vector_free(&v);
}

void test_vector_free(){
    vector v;
    v = create_uninitialized_vector();
    CU_ASSERT(vector_free(&v) == uninitialized);
    vector_init(&v);
    vector_push(&v, 1);
    CU_ASSERT(vector_free(&v) == ok);
    CU_ASSERT(v.content == NULL && v.length == 0 && v.capacity == 0);
}

void test_vector_map(){

    vector v, v2;
    v = create_uninitialized_vector();
    CU_ASSERT(vector_map(&v, square, &v2) == uninitialized);

    vector_init(&v);
    vector_push(&v, 1);
    vector_push(&v, 2);
    vector_push(&v, 3);
    vector_push(&v, 4);
    vector_init(&v2);
    CU_ASSERT(vector_map(&v, square, &v2) == ok);

    CU_ASSERT(v.length == v2.length);
    for(int i=0; i<v.length; i++){
        type element, element2;
        vector_get(&v, i, &element);
        vector_get(&v2, i, &element2);
        CU_ASSERT(element2 == element*element);
    }

    vector_free(&v);
    vector_free(&v2);
}

void test_vector_filter(){
    vector v, v2, vtest;
    v = create_uninitialized_vector();
    CU_ASSERT(vector_filter(&v, is_even, &v2) == uninitialized);

    vector_init(&v);
    vector_init(&vtest);
    vector_init(&v2);

    vector_push(&v, 1);
    vector_push(&v, 2);
    vector_push(&v, 16);
    vector_push(&v, 11);
    vector_push(&v, 13);
    vector_push(&v, 100);
    vector_push(&v, 1);

    vector_push(&vtest, 2);
    vector_push(&vtest, 16);
    vector_push(&vtest, 100);

    CU_ASSERT(vector_filter(&v, is_even, &v2) == ok);

    CU_ASSERT(vector_is_equal(&v2, &vtest));

    vector_free(&v);
    vector_free(&v2);
    vector_free(&vtest);
}
