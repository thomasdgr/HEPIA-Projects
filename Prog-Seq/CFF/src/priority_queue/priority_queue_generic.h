#ifndef priority_queue_GENERIC_H
#define priority_queue_GENERIC_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "priority_queue.h"

typedef struct g_element{
    void *data;
    struct g_element* next;
} g_element;

typedef struct priority_queue_generic {
    int length;
    struct g_element* head;
} priority_queue_generic;

error_code priority_queue_generic_init(priority_queue_generic *v);
error_code priority_queue_generic_push(priority_queue_generic *v, void* elements, bool (*cmp)(void*, void*));
error_code priority_queue_generic_pop(priority_queue_generic *v, void** n);
error_code priority_queue_generic_peek(priority_queue_generic *v, void** n);
error_code priority_queue_generic_empty(priority_queue_generic *v);
error_code priority_queue_generic_free(priority_queue_generic *v);
void priority_queue_generic_print_int(priority_queue_generic *v);
bool priority_queue_generic_is_empty(priority_queue_generic *v);
bool cmp_generic(void* i, void* j);

#endif
