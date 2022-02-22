/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de liste chainées pour le stockage de point_2d
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_list_2d.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

error_code lst_vector_2d_init(lst_vector_2d *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code lst_vector_2d_length(lst_vector_2d *v, int *length) {
    *length = v->length;
    return ok;
}

error_code lst_vector_2d_push(lst_vector_2d *v, point_2d elements) {
    element_2d *elem = malloc(sizeof(element_2d));
    elem->data = elements;
    elem->next = v->head;
    v->head = elem;
    v->length++;
    return ok;
}

error_code lst_vector_2d_pop(lst_vector_2d *v, point_2d *elements) {
    if(NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_2d_pop");
      return out_of_bounds;
    }
    element_2d *first = v->head;
    *elements = first->data;
    v->head = first->next;
    v->length--;
    free(first);
    return ok;
}

bool lst_vector_2d_is_equal(lst_vector_2d *v1, lst_vector_2d *v2) {
    if(v1->head == NULL || v2->head == NULL){
      return true;
    }
    int size1 = 0, size2 = 0;
    lst_vector_2d_length(v1, &size1);
    lst_vector_2d_length(v2, &size2);
    if(size1 != size2){
      return false;
    }
    point_2d tmp1 = {0,0};
    point_2d tmp2 = {0,0};
    for (int i = 0; i < size1; i++){
        lst_vector_2d_get(v1, i, &tmp1);
        lst_vector_2d_get(v2, i, &tmp2);
        if ((tmp1.x != tmp2.x) || (tmp1.y != tmp2.y)){
          return false;
        }
    }
    return true;
}

error_code print_lst_vector_2d (lst_vector_2d *v) {
    element_2d *tmp = v->head;
    while (tmp != NULL){
        printf("tmp.x: %f/tmp.y: %f ", tmp->data.x, tmp->data.y);
        tmp = tmp->next;
    }
    return ok;
}

error_code lst_vector_2d_set(lst_vector_2d *v, int index, point_2d elements) {
    int size = 0;
    lst_vector_2d_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_2d_set");
      return out_of_bounds;
    }
    int i = 0;
    element_2d *tmp = v->head;
    while (i != index){
        i ++;
        tmp = tmp->next;
    }
    tmp->data = elements;
    return ok;
}

error_code lst_vector_2d_get(lst_vector_2d *v, int index, point_2d *element) {
    int size = 0;
    lst_vector_2d_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_2d_get");
      return out_of_bounds;
    }
    int i = 0;
    lst_vector_2d tmp = *v;
    while (i != index){
        i ++;
        tmp.head = tmp.head->next;
    }
    *element = tmp.head->data;
    return ok;
}

error_code lst_vector_2d_remove(lst_vector_2d *v, int index) {
    if (index == 0){
        point_2d none;
        if(lst_vector_2d_pop(v, &none) == ok){
          return ok;
        } else {
          error_code_display(out_of_bounds, "lst_vector_2d_remove");
          return out_of_bounds;
        }
    }
    int size = 0;
    lst_vector_2d_length(v, &size);
    if(index < 0 || index >= size){
      error_code_display(out_of_bounds, "lst_vector_2d_remove");
      return out_of_bounds;
    }
    int i = 0;
    element_2d *tmp = NULL;
    element_2d *elem_replace = v->head;

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

error_code lst_vector_2d_insert(lst_vector_2d *v, point_2d elements, int index) {
    int size = 0;
    lst_vector_2d_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_2d_insert");
      return out_of_bounds;
    }
    if(index == 0){
      lst_vector_2d_push(v, elements);
    }
    int i = 0;
    element_2d *tmp = NULL;
    element_2d *elem_replace = v->head;
    element_2d *elem = malloc(sizeof(element_2d));
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

error_code lst_vector_2d_empty(lst_vector_2d *v) {
    lst_vector_2d_free(v);
    v->length = 0;  
    return ok;
}

error_code lst_vector_2d_free(lst_vector_2d *v) {
    if(v->head == NULL){
      return memory_error;
    }
    point_2d trash;
    while (v->head != NULL){
      lst_vector_2d_pop(v, &trash);
    }
    return ok;
}

error_code lst_vector_2d_map(lst_vector_2d *v, point_2d (*f)(point_2d), lst_vector_2d *rhs) {
    lst_vector_2d_init(rhs);
    point_2d tmp = {0,0};
    int size = 0;
    lst_vector_2d_length(v, &size);
    for (int i = 0; i < size; i++){
      lst_vector_2d_push(rhs, tmp);
    }
    for (int i = 0; i < size; i++){
        if (lst_vector_2d_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_2d_map");
          return memory_error;
        }
        if (lst_vector_2d_set(rhs, i, f(tmp)) == memory_error){
          error_code_display(memory_error, "lst_vector_2d_map");
          return memory_error;
        }
    }
    return ok;
}

error_code lst_vector_2d_filter(lst_vector_2d *v, bool (*f)(point_2d), lst_vector_2d *rhs) {
    point_2d tmp = {0,0};
    int size = 0;
    lst_vector_2d_length(v, &size);
    for (int i = 0; i < size; i++){
        if (lst_vector_2d_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_2d_filter");
          return memory_error;
        }
        if (f(tmp)){
          lst_vector_2d_push(rhs, tmp);
        }
    }
    return ok;
}
