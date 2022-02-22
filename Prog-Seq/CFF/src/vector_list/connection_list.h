#ifndef CONNECTION_LIST_H
#define CONNECTION_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <assert.h>
#include "../error/error.h"
#include "city_list.h"

typedef struct connection {
    int neighbor;
    int weight;
    struct connection* next;
} connection;

typedef struct lst_connection {
    int length;
    struct connection* head;
} lst_connection;

error_code lst_connection_init(lst_connection *v); // initializes an empty vector of site VECTOR_INIT_CAPAconnection size
error_code lst_tab_connection_init(lst_connection **v, int taille);
error_code lst_connection_length(lst_connection *v, int* length); // stores the length of v in length
error_code lst_connection_push(lst_connection *v, connection *n); // push an connection
error_code lst_connection_pop(lst_connection *v, connection *n); // pop the last connection
error_code lst_connection_set(lst_connection *v, int index, connection *n); // set index-th connection
error_code lst_connection_get(lst_connection *v, int index, connection *n); // stores index-th connection in *connection
error_code lst_connection_remove(lst_connection *v, int index); // remove index-th connection
error_code lst_connection_insert(lst_connection *v, connection *n, int index); // insert connection at position index
error_code lst_connection_empty(lst_connection *v);
error_code lst_connection_free(lst_connection *v);

error_code print_lst_connection(lst_connection *v);

error_code lst_connection_default_value(lst_connection *v);
error_code lst_connection_resize(lst_connection *v, int size);
connection lst_connection_get_last_element(lst_connection v);
bool lst_connection_is_valid(lst_connection *v);
bool lst_connection_is_empty(lst_connection *v);
error_code tab_connection_free(lst_connection* tab, int size);
error_code print_lst_tab_connection (lst_connection *v);

#endif
