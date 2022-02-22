/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de liste chainées pour le stockage de int (définit comme "type")
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

error_code lst_vector_init(lst_vector *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code lst_vector_length(lst_vector *v, int *length) {
    *length = v->length;
    return ok;
}

error_code lst_vector_push(lst_vector *v, type elements) {
    element *elem = malloc(sizeof(element));
    elem->data = elements;
    elem->next = v->head;
    v->head = elem;
    v->length++;
    return ok;
}

error_code lst_vector_pop(lst_vector *v, type *elements) {
    if(NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_pop");
      return out_of_bounds;
    }
    element *first = v->head;
    *elements = first->data;
    v->head = first->next;
    v->length--;
    free(first);
    return ok;
}

bool lst_vector_is_equal(lst_vector *v1, lst_vector *v2) {
    if(v1->head == NULL || v2->head == NULL){
      return true;
    }
    int size1 = 0, size2 = 0;
    lst_vector_length(v1, &size1);
    lst_vector_length(v2, &size2);
    if(size1 != size2){
      return false;
    }
    type tmp1 = 0, tmp2 = 0;
    for (int i = 0; i < size1; i++){
        lst_vector_get(v1, i, &tmp1);
        lst_vector_get(v2, i, &tmp2);
        if (tmp1 != tmp2){
          return false;
        }
    }
    return true;
}

error_code print_vector (lst_vector *v) {
    element *tmp = v->head;
    while (tmp != NULL){
        printf(" %d ", tmp->data);
        tmp = tmp->next;
    }
    return ok;
}

error_code lst_vector_set(lst_vector *v, int index, type elements) {
    int size = 0;
    lst_vector_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_set");
      return out_of_bounds;
    }
    int i = 0;
    element *tmp = v->head;
    while (i != index){
        i ++;
        tmp = tmp->next;
    }
    tmp->data = elements;
    return ok;
}

error_code lst_vector_get(lst_vector *v, int index, type *element) {
    int size = 0;
    lst_vector_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_get");
      return out_of_bounds;
    }
    int i = 0;
    lst_vector tmp = *v;
    while (i != index){
        i ++;
        tmp.head = tmp.head->next;
    }
    *element = tmp.head->data;
    return ok;
}

error_code lst_vector_remove(lst_vector *v, int index) {
    if (index == 0){
        int none;
        if(lst_vector_pop(v, &none) == ok){
          return ok;
        } else {
          error_code_display(out_of_bounds, "lst_vector_remove");
          return out_of_bounds;
        }
    }
    int size = 0;
    lst_vector_length(v, &size);
    if(index < 0 || index >= size){
      error_code_display(out_of_bounds, "lst_vector_remove");
      return out_of_bounds;
    }
    int i = 0;
    element *tmp = NULL;
    element *elem_replace = v->head;

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

error_code lst_vector_insert(lst_vector *v, type elements, int index) {
    int size = 0;
    lst_vector_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_insert");
      return out_of_bounds;
    }
    if(index == 0){
      lst_vector_push(v, elements);
    }
    int i = 0;
    element *tmp = NULL;
    element *elem_replace = v->head;
    element *elem = malloc(sizeof(element));
    elem->data = elements;
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

error_code lst_vector_empty(lst_vector *v) {
    lst_vector_free(v);
    v->length = 0;
    return ok;
}

error_code lst_vector_free(lst_vector *v) {
    if(v->head == NULL){
      return memory_error;
    }
    type trash;
    while (v->head != NULL){
      lst_vector_pop(v, &trash);
    }
    return ok;
}

error_code lst_vector_map(lst_vector *v, type (*f)(type), lst_vector *rhs) {
    lst_vector_init(rhs);
    type tmp = 0;
    int size = 0;
    lst_vector_length(v, &size);
    for (int i = 0; i < size; i++){
      lst_vector_push(rhs, 0);
    }
    for (int i = 0; i < size; i++){
        if (lst_vector_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_map");
          return memory_error;
        }
        if (lst_vector_set(rhs, i, f(tmp)) == memory_error){
          error_code_display(memory_error, "lst_vector_map");
          return memory_error;
        }
    }
    return ok;
}

error_code lst_vector_filter(lst_vector *v, bool (*f)(type), lst_vector *rhs) {
    type tmp = 0;
    int size = 0;
    lst_vector_length(v, &size);
    for (int i = 0; i < size; i++){
        if (lst_vector_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_filter");
          return memory_error;
        }
        if (f(tmp)){
          lst_vector_push(rhs, tmp);
        }
    }
    return ok;
}
