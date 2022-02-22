#ifndef priority_queue_H
#define priority_queue_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../error/error.h"

typedef struct element {
    int data;
    struct element* next;
} element;

typedef struct priority_queue {
    int length;
    struct element* head;
} priority_queue;

error_code priority_queue_init(priority_queue *v);
error_code priority_queue_push(priority_queue *v, int elements, bool (*cmp)(int, int));
error_code priority_queue_pop(priority_queue *v, int *n);
error_code priority_queue_peek(priority_queue *v, int *n);
error_code priority_queue_empty(priority_queue *v);
error_code priority_queue_free(priority_queue *v);
void priority_queue_print_int(priority_queue *v);
bool priority_queue_is_empty(priority_queue *v);
bool cmp(int i, int j);

#endif
