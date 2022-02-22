#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "../error/error.h"

#define INIT_CAPACITY 4

typedef struct hpq {
    int* data;
    int length;
    int capacity;
} hpq;

void print_tab(int size, int tab[]);
int trouver_fils_gauche(int i);
int trouver_fils_droit(int i);
void swap(int * a, int * b);
int max3(int size, int tab[], int i);
void promotion(int size, int tab[],int i);
void entassement(int size, int tab[]);
void heapsort(int size, int tab[]);

error_code hpq_init(hpq *v); // initializes an empty hpq of site hpq_INIT_CAPACITY size
error_code hpq_push(hpq *v, int element); // push an element
error_code hpq_pop(hpq *v, int *element); // pop the last element
error_code hpq_empty(hpq *v);
error_code hpq_free(hpq *v);
error_code hpq_peek(hpq *v, int *elements);
error_code hpq_default_value(hpq *v);
error_code hpq_resize(hpq *v, int size);

void hpq_print_int(hpq *v);
bool hpq_is_valid(hpq v);
bool hpq_is_full(hpq v);
bool hpq_is_empty(hpq v);

#endif