#include "test_list.h"
#include "../vector_list/city_list.h"
#include "../vector_list/connection_list.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_city_list(){
    city* a = malloc(sizeof(city));
    a->latitude = 1;
    a->longitude = 1;
    a->next = NULL;
    strcpy(a->name, "geneve");

    city* b = malloc(sizeof(city));
    b->latitude = 2;
    b->longitude = 2;
    b->next = NULL;
    strcpy(b->name, "lausanne");

    city* c = malloc(sizeof(city));
    c->latitude = 3;
    c->longitude = 3;
    c->next = NULL;
    strcpy(a->name, "bale");

    city* d = malloc(sizeof(city));
    d->latitude = 4;
    d->longitude = 4;
    d->next = NULL;
    strcpy(d->name, "zurich");

    city* e = malloc(sizeof(city));
    e->latitude = 5;
    e->longitude = 5;
    e->next = NULL;
    strcpy(e->name, "lucern");

    lst_city v;
    lst_city_init(&v);
    lst_city_push(&v, a);
    lst_city_push(&v, b);
    lst_city_push(&v, c);
    lst_city_push(&v, d);
    lst_city_push(&v, e);
    
    city* result = malloc(sizeof(city));
    lst_city_get(&v, 2, result);
    CU_ASSERT(result->latitude == 3);
    CU_ASSERT(result->longitude == 3);

    lst_city_pop(&v, result);
    CU_ASSERT(result->latitude == 1);
    CU_ASSERT(result->longitude == 1);
    int length;
    lst_city_length(&v, &length);
    CU_ASSERT(length == 4);

    lst_city_remove(&v,2);
    lst_city_length(&v, &length);
    CU_ASSERT(length == 3);

    city* fribourg = malloc(sizeof(city));
    fribourg->latitude = 6;
    fribourg->longitude = 6;
    fribourg->next = NULL;
    lst_city_insert(&v,fribourg,3);
    lst_city_length(&v, &length);
    CU_ASSERT(length == 4);
    lst_city_get(&v, 3, result);
    CU_ASSERT(result->latitude == 6);
    CU_ASSERT(result->longitude== 6);

    lst_city_empty(&v);
    lst_city_length(&v, &length);
    CU_ASSERT(length == 0);

    lst_city_free(&v);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(result);
}

void test_connection_list(){
    connection* a = malloc(sizeof(connection));
    a->neighbor = 1;
    a->weight = 1;
    a->next = NULL;

    connection* b = malloc(sizeof(connection));
    b->neighbor = 1;
    b->weight = 1;
    b->next = NULL;

    connection* c = malloc(sizeof(connection));
    c->neighbor = 1;
    c->weight = 1;
    a->next = NULL;

    connection* d = malloc(sizeof(connection));
    d->neighbor = 1;
    d->weight = 1;
    d->next = NULL;

    connection* e = malloc(sizeof(connection));
    e->neighbor = 1;
    e->weight = 1;
    e->next = NULL;

    lst_connection v;
    lst_connection_init(&v);
    lst_connection_push(&v, a);
    lst_connection_push(&v, b);
    lst_connection_push(&v, c);
    lst_connection_push(&v, d);
    lst_connection_push(&v, e);
    
    connection* result = malloc(sizeof(connection));
    lst_connection_get(&v, 2, result);
    CU_ASSERT(result->neighbor == 1);
    CU_ASSERT(result->weight == 1);

    lst_connection_pop(&v, result);
    CU_ASSERT(result->neighbor == 1);
    CU_ASSERT(result->weight == 1);
    int length;
    lst_connection_length(&v, &length);
    CU_ASSERT(length == 4);

    lst_connection_remove(&v,2);
    lst_connection_length(&v, &length);
    CU_ASSERT(length == 3);

    connection* fribourg = malloc(sizeof(connection));
    fribourg->neighbor = 6;
    fribourg->weight = 6;
    fribourg->next = NULL;
    lst_connection_insert(&v,fribourg,3);
    lst_connection_length(&v, &length);
    CU_ASSERT(length == 4);
    lst_connection_get(&v, 3, result);
    CU_ASSERT(result->neighbor == 6);
    CU_ASSERT(result->weight == 6);

    lst_connection_empty(&v);
    lst_connection_length(&v, &length);
    CU_ASSERT(length == 0);

    lst_connection_free(&v);
    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(result);
}