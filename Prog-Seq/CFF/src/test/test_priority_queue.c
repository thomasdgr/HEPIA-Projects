#include "test_priority_queue.h"
#include "../priority_queue/priority_queue_generic.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_priority_queue(){
    priority_queue v;
    priority_queue_init(&v);

    priority_queue_push(&v, 2, cmp);
    priority_queue_push(&v, 9, cmp);
    priority_queue_push(&v, 5, cmp);
    priority_queue_push(&v, 1, cmp);
    priority_queue_push(&v, 6, cmp);
    priority_queue_push(&v, 10, cmp);
    priority_queue_push(&v, 7, cmp);
    priority_queue_push(&v, 4, cmp);
    priority_queue_push(&v, 8, cmp);
    priority_queue_push(&v, 3, cmp);
    priority_queue_push(&v, 11, cmp);

    int *value = malloc(sizeof(int));
    priority_queue_pop(&v, value);
    CU_ASSERT(*value == 11);
    CU_ASSERT(v.length == 10);

    priority_queue_peek(&v, value);
    CU_ASSERT(*value == 10);
    CU_ASSERT(v.length == 10);

    priority_queue_empty(&v);
    CU_ASSERT(priority_queue_is_empty(&v) == true);

    priority_queue_free(&v);
    free(value);
}

void test_priority_queue_generic(){
    priority_queue_generic v2;
    priority_queue_generic_init(&v2);
    
    int tmp[10];
    for(int i = 0; i < 10; i++){
        tmp[i] = i;
        priority_queue_generic_push(&v2, (void*)(tmp+i), cmp_generic);
    }

    int* tmp2;
    priority_queue_generic_pop(&v2, (void**)&tmp2);
    CU_ASSERT(*(int*)tmp2 == 9);
    CU_ASSERT(v2.length == 9);

    int* tmp3;
    priority_queue_generic_peek(&v2, (void**)&tmp3);
    CU_ASSERT(*(int*)tmp3 == 8);
    CU_ASSERT(v2.length == 9);

    priority_queue_generic_empty(&v2);
    CU_ASSERT(priority_queue_generic_is_empty(&v2) == true);

    priority_queue_generic_free(&v2);
}