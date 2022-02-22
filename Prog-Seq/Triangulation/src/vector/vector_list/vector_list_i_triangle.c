/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de liste chainées pour le stockage de i_triangle 
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_list_i_triangle.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

error_code lst_vector_i_triangle_init(lst_vector_i_triangle *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code lst_vector_i_triangle_length(lst_vector_i_triangle *v, int *length) {
    *length = v->length;
    return ok;
}

error_code lst_vector_i_triangle_push(lst_vector_i_triangle *v, i_triangle elements) {
    element_i_triangle *elem = malloc(sizeof(element_i_triangle));
    elem->data = elements;
    elem->next = v->head;
    v->head = elem;
    v->length++;
    return ok;
}

error_code lst_vector_i_triangle_pop(lst_vector_i_triangle *v, i_triangle *elements) {
    if(NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_i_triangle_pop");
      return out_of_bounds;
    }
    element_i_triangle *first = v->head;
    *elements = first->data;
    v->head = first->next;
    v->length--;
    free(first);
    return ok;
}

bool lst_vector_i_triangle_is_equal(lst_vector_i_triangle *v1, lst_vector_i_triangle *v2) {
    if(v1->head == NULL || v2->head == NULL){
      return true;
    }
    int size1 = 0, size2 = 0;
    lst_vector_i_triangle_length(v1, &size1);
    lst_vector_i_triangle_length(v2, &size2);
    if(size1 != size2){
      return false;
    }
    i_triangle tmp1 = {0,0,0};
    i_triangle tmp2 = {0,0,0};
    for (int i = 0; i < size1; i++){
        lst_vector_i_triangle_get(v1, i, &tmp1);
        lst_vector_i_triangle_get(v2, i, &tmp2);
        if ((tmp1.p1 != tmp2.p1) || (tmp1.p2 != tmp2.p2) || (tmp1.p3 != tmp2.p3)){
          return false;
        }
    }
    return true;
}

error_code print_lst_vector_i_triangle (lst_vector_i_triangle *v) {
    element_i_triangle *tmp = v->head;
    while (tmp != NULL){
        printf("tmp.p1:%d/tmp.p2:%d/tmp.p3:%d/ ", tmp->data.p1, tmp->data.p2, tmp->data.p3);
        tmp = tmp->next;
    }
    return ok;
}

error_code lst_vector_i_triangle_set(lst_vector_i_triangle *v, int index, i_triangle elements) {
    int size = 0;
    lst_vector_i_triangle_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_i_triangle_set");
      return out_of_bounds;
    }
    int i = 0;
    element_i_triangle *tmp = v->head;
    while (i != index){
        i ++;
        tmp = tmp->next;
    }
    tmp->data = elements;
    return ok;
}

error_code lst_vector_i_triangle_get(lst_vector_i_triangle *v, int index, i_triangle *element) {
    int size = 0;
    lst_vector_i_triangle_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_i_triangle_get");
      return out_of_bounds;
    }
    int i = 0;
    lst_vector_i_triangle tmp = *v;
    while (i != index){
        i ++;
        tmp.head = tmp.head->next;
    }
    *element = tmp.head->data;
    return ok;
}

error_code lst_vector_i_triangle_remove(lst_vector_i_triangle *v, int index) {
    if (index == 0){
        i_triangle none;
        if(lst_vector_i_triangle_pop(v, &none) == ok){
          return ok;
        } else {
          error_code_display(out_of_bounds, "lst_vector_i_triangle_remove");
          return out_of_bounds;
        }
    }
    int size = 0;
    lst_vector_i_triangle_length(v, &size);
    if(index < 0 || index >= size){
      error_code_display(out_of_bounds, "lst_vector_i_triangle_remove");
      return out_of_bounds;
    }
    int i = 0;
    element_i_triangle *tmp = NULL;
    element_i_triangle *elem_replace = v->head;

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

error_code lst_vector_i_triangle_insert(lst_vector_i_triangle *v, i_triangle elements, int index) {
    int size = 0;
    lst_vector_i_triangle_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_i_triangle_insert");
      return out_of_bounds;
    }
    if(index == 0){
      lst_vector_i_triangle_push(v, elements);
    }
    int i = 0;
    element_i_triangle *tmp = NULL;
    element_i_triangle *elem_replace = v->head;
    element_i_triangle *elem = malloc(sizeof(element_i_triangle));
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

error_code lst_vector_i_triangle_empty(lst_vector_i_triangle *v) {
    lst_vector_i_triangle_free(v);
    v->length = 0;
    return ok;
}

error_code lst_vector_i_triangle_free(lst_vector_i_triangle *v) {
    if(v->head == NULL){
      return memory_error;
    }
    i_triangle trash;
    while (v->head != NULL){
      lst_vector_i_triangle_pop(v, &trash);
    }
    return ok;
}

error_code lst_vector_i_triangle_map(lst_vector_i_triangle *v, i_triangle (*f)(i_triangle), lst_vector_i_triangle *rhs) {
    lst_vector_i_triangle_init(rhs);
    i_triangle tmp = {0,0,0};
    int size = 0;
    lst_vector_i_triangle_length(v, &size);
    for (int i = 0; i < size; i++){
      lst_vector_i_triangle_push(rhs, tmp);
    }
    for (int i = 0; i < size; i++){
        if (lst_vector_i_triangle_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_i_triangle_map");
          return memory_error;
        }
        if (lst_vector_i_triangle_set(rhs, i, f(tmp)) == memory_error){
          error_code_display(memory_error, "lst_vector_i_triangle_map");
          return memory_error;
        }
    }
    return ok;
}

error_code lst_vector_i_triangle_filter(lst_vector_i_triangle *v, bool (*f)(i_triangle), lst_vector_i_triangle *rhs) {
    i_triangle tmp = {0,0,0};
    int size = 0;
    lst_vector_i_triangle_length(v, &size);
    for (int i = 0; i < size; i++){
        if (lst_vector_i_triangle_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_i_triangle_filter");
          return memory_error;
        }
        if (f(tmp)){
          lst_vector_i_triangle_push(rhs, tmp);
        }
    }
    return ok;
}
