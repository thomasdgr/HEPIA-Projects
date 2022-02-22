/*******************************************************************************
			       ____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour stocker des voisins dans
(___) \.  _.\__. `\___           |    une liste specifique. On utilisera une liste
(___)  )\/  \_____/  ~\.         |    de liste pour créer une liste d'adjacence
(___) . \   `         `\         |   
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	03/06/2020

\******************************************************************************/

#include "connection_list.h"

error_code lst_connection_init(lst_connection *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code lst_tab_connection_init(lst_connection **v, int taille) {
    *v = malloc(sizeof(lst_connection) * taille);
    for(int i = 0; i < taille; i++){
      lst_connection_init(*v+i);
    }
    return ok;  
}

error_code lst_connection_length(lst_connection *v, int *length) {
    *length = v->length;
    return ok;
}

error_code lst_connection_push(lst_connection *v, connection *elements) {
    connection *alo = malloc(sizeof(connection));
    alo->neighbor = elements->neighbor;
    alo->weight = elements->weight;
    alo->next = NULL;
    if(v->length == 0){
      v->head = alo;
    } else {
      connection *elem = v->head;
      v->head = alo;
      alo->next = elem;
    }
    v->length++;
    return ok;
}

error_code lst_connection_pop(lst_connection *v, connection *elements) {
    if(NULL == v->head){
      error_code_display(out_of_bounds, "lst_connection_pop");
      return out_of_bounds;
    }
    connection *first = v->head;
    *elements = *first;
    v->head = first->next;
    v->length--;
    free(first);
    return ok;
}

error_code print_lst_connection (lst_connection *v) {
    connection *tmp = v->head;
    while (tmp != NULL){
        printf("[%s:%d] ", get_city_from_index(tmp->neighbor), tmp->weight);
        tmp = tmp->next;
    }
    printf("\n");
    return ok;
}

error_code print_lst_tab_connection (lst_connection *v) {
    for(int i = 0; i < 15; i++){
        printf("%s ",get_city_from_index(i));
        print_lst_connection(&v[i]);
    }
    return ok;
}

error_code lst_connection_set(lst_connection *v, int index, connection *elements) {
    int size = 0;
    lst_connection_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_connection_set");
      return out_of_bounds;
    }
    int i = 0;
    connection *tmp = v->head;
    while (i != index){
        i ++;
        tmp = tmp->next;
    }
    tmp = elements;
    return ok;
}

error_code lst_connection_get(lst_connection *v, int index, connection *element) {
    int size = 0;
    lst_connection_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_connection_get");
      return out_of_bounds;
    }
    int i = 0;
    lst_connection tmp = *v;
    while (i != index){
        i ++;
        tmp.head = tmp.head->next;
    }
    *element = *tmp.head;
    return ok;
}

error_code lst_connection_remove(lst_connection *v, int index) {
    if (index == 0){
        connection none;
        if(lst_connection_pop(v, &none) == ok){
          return ok;
        } else {
          error_code_display(out_of_bounds, "lst_connection_remove");
          return out_of_bounds;
        }
    }
    int size = 0;
    lst_connection_length(v, &size);
    if(index < 0 || index >= size){
      error_code_display(out_of_bounds, "lst_connection_remove");
      return out_of_bounds;
    }
    int i = 0;
    connection *tmp = NULL;
    connection *elem_replace = v->head;

    while (i != index){
        if(i == (index - 1)){
          tmp = elem_replace;
        }
        elem_replace = elem_replace->next;
        i ++;
    }

    tmp->next = elem_replace->next;
    v->length--;
    free(elem_replace);
    return ok;
}

error_code lst_connection_insert(lst_connection *v, connection *elements, int index) {
    int size = 0;
    lst_connection_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_connection_insert");
      return out_of_bounds;
    }
    if(index == 0){
      lst_connection_push(v, elements);
    }
    int i = 0;
    connection *tmp = NULL;
    connection *elem_replace = v->head;
    connection *elem = malloc(sizeof(connection));
    elem = elements;
    while (i != index){
        if(i == index - 1){
          tmp = elem_replace;
        }
        elem_replace = elem_replace->next;
        i ++;
    }
    tmp->next = elem;
    v->length++;
    elem->next = elem_replace;
    return ok;
}

error_code lst_connection_empty(lst_connection *v) {
    lst_connection_free(v);
    v->length = 0;
    return ok;
}

error_code lst_connection_free(lst_connection *v) {
    if(v->head== NULL){
      return memory_error;
    }
    connection trash;
    while (v->head!= NULL){
      lst_connection_pop(v, &trash);
    }
    return ok;
}

error_code tab_connection_free(lst_connection* tab, int size){
    if(tab->head== NULL){
      return memory_error;
    }
    for(int i = 0; i < size; i++){
      lst_connection_free(tab+i);
    }
    free(tab);
    return ok;
}