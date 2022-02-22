#ifndef CITY_LIST_H
#define CITY_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../error/error.h"

#define NAME_LEN 50
typedef struct city {
    char name[NAME_LEN];
    int longitude;
    int latitude;
    struct city* next;
} city;

typedef struct lst_city {
    int length;
    struct city* head;
} lst_city;

error_code lst_city_init(lst_city *v); // initializes an empty vector of site VECTOR_INIT_CAPACITY size
error_code lst_city_length(lst_city *v, int* length); // stores the length of v in length
error_code lst_city_push(lst_city *v, city *n); // push an city
error_code lst_city_pop(lst_city *v, city *n); // pop the last city
error_code lst_city_set(lst_city *v, int index, city *n); // set index-th city
error_code lst_city_get(lst_city *v, int index, city *n); // stores index-th city in *city
error_code lst_city_remove(lst_city *v, int index); // remove index-th city
error_code lst_city_insert(lst_city *v, city *n, int index); // insert city at position index
error_code lst_city_empty(lst_city *v);
error_code lst_city_free(lst_city *v);

error_code print_lst_city(lst_city *v);

char* get_city_from_index(int index);
int get_index_from_city(char* city);

error_code lst_city_default_value(lst_city *v);
error_code lst_city_resize(lst_city *v, int size);
city lst_city_get_last_element(lst_city v);
bool lst_city_is_valid(lst_city *v);
bool lst_city_is_empty(lst_city *v);

#endif
