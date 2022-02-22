/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de liste chainées pour le stockage de point_3d 
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_list_3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

error_code lst_vector_3d_init(lst_vector_3d *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code lst_vector_3d_length(lst_vector_3d *v, int *length) {
    *length = v->length;
    return ok;
}

error_code lst_vector_3d_push(lst_vector_3d *v, point_3d elements) {
    element_3d *elem = malloc(sizeof(element_3d));
    elem->data = elements;
    elem->next = v->head;
    v->head = elem;
    v->length++;
    return ok;
}

error_code lst_vector_3d_pop(lst_vector_3d *v, point_3d *elements) {
    if(NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_3d_pop");
      return out_of_bounds;
    }
    element_3d *first = v->head;
    *elements = first->data;
    v->head = first->next;
    v->length--;
    free(first);
    return ok;
}

bool lst_vector_3d_is_equal(lst_vector_3d *v1, lst_vector_3d *v2) {
    if(v1->head == NULL || v2->head == NULL){
      return true;
    }
    int size1 = 0, size2 = 0;
    lst_vector_3d_length(v1, &size1);
    lst_vector_3d_length(v2, &size2);
    if(size1 != size2){
      return false;
    }
    point_3d tmp1 = {0,0,0};
    point_3d tmp2 = {0,0,0};
    for (int i = 0; i < size1; i++){
        lst_vector_3d_get(v1, i, &tmp1);
        lst_vector_3d_get(v2, i, &tmp2);
        if ((tmp1.x != tmp2.x) || (tmp1.y != tmp2.y) || (tmp1.z != tmp2.z)){
          return false;
        }
    }
    return true;
}

error_code print_lst_vector_3d (lst_vector_3d *v) {
    element_3d *tmp = v->head;
    while (tmp != NULL){
        printf("tmp.x: %f/tmp.y: %f/tmp.z: %f", tmp->data.x, tmp->data.y, tmp->data.z);
        tmp = tmp->next;
    }
    return ok;
}

error_code lst_vector_3d_set(lst_vector_3d *v, int index, point_3d elements) {
    int size = 0;
    lst_vector_3d_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_3d_set");
      return out_of_bounds;
    }
    int i = 0;
    element_3d *tmp = v->head;
    while (i != index){
        i ++;
        tmp = tmp->next;
    }
    tmp->data = elements;
    return ok;
}

error_code lst_vector_3d_get(lst_vector_3d *v, int index, point_3d *element) {
    int size = 0;
    lst_vector_3d_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_3d_get");
      return out_of_bounds;
    }
    int i = 0;
    lst_vector_3d tmp = *v;
    while (i != index){
        i ++;
        tmp.head = tmp.head->next;
    }
    *element = tmp.head->data;
    return ok;
}

error_code lst_vector_3d_remove(lst_vector_3d *v, int index) {
    if (index == 0){
        point_3d none;
        if(lst_vector_3d_pop(v, &none) == ok){
          return ok;
        } else {
          error_code_display(out_of_bounds, "lst_vector_3d_remove");
          return out_of_bounds;
        }
    }
    int size = 0;
    lst_vector_3d_length(v, &size);
    if(index < 0 || index >= size){
      error_code_display(out_of_bounds, "lst_vector_3d_remove");
      return out_of_bounds;
    }
    int i = 0;
    element_3d *tmp = NULL;
    element_3d *elem_replace = v->head;

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

error_code lst_vector_3d_insert(lst_vector_3d *v, point_3d elements, int index) {
    int size = 0;
    lst_vector_3d_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_3d_insert");
      return out_of_bounds;
    }
    if(index == 0){
      lst_vector_3d_push(v, elements);
    }
    int i = 0;
    element_3d *tmp = NULL;
    element_3d *elem_replace = v->head;
    element_3d *elem = malloc(sizeof(element_3d));
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

error_code lst_vector_3d_empty(lst_vector_3d *v) {
    lst_vector_3d_free(v);
    v->length = 0;
    return ok;
}

error_code lst_vector_3d_free(lst_vector_3d *v) {
    if(v->head== NULL){
      return memory_error;
    }
    point_3d trash;
    while (v->head!= NULL){
      lst_vector_3d_pop(v, &trash);
    }
    return ok;
}

error_code lst_vector_3d_map(lst_vector_3d *v, point_3d (*f)(point_3d), lst_vector_3d *rhs) {
    lst_vector_3d_init(rhs);
    point_3d tmp = {0,0,0};
    int size = 0;
    lst_vector_3d_length(v, &size);
    for (int i = 0; i < size; i++){
      lst_vector_3d_push(rhs, tmp);
    }
    for (int i = 0; i < size; i++){
        if (lst_vector_3d_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_3d_map");
          return memory_error;
        }
        if (lst_vector_3d_set(rhs, i, f(tmp)) == memory_error){
          error_code_display(memory_error, "lst_vector_3d_map");
          return memory_error;
        }
    }
    return ok;
}

error_code lst_vector_3d_filter(lst_vector_3d *v, bool (*f)(point_3d), lst_vector_3d *rhs) {
    point_3d tmp = {0,0,0};
    int size = 0;
    lst_vector_3d_length(v, &size);
    for (int i = 0; i < size; i++){
        if (lst_vector_3d_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_3d_filter");
          return memory_error;
        }
        if (f(tmp)){
          lst_vector_3d_push(rhs, tmp);
        }
    }
    return ok;
}
