/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de liste chainées pour le stockage de i_edge
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_list_i_edge.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

error_code lst_vector_i_edge_init(lst_vector_i_edge *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code lst_vector_i_edge_length(lst_vector_i_edge *v, int *length) {
    *length = v->length;
    return ok;
}

error_code lst_vector_i_edge_push(lst_vector_i_edge *v, i_edge elements) {
    element_i_edge *elem = malloc(sizeof(element_i_edge));
    elem->data = elements;
    elem->next = v->head;
    v->head = elem;
    v->length++;
    return ok;
}

error_code lst_vector_i_edge_pop(lst_vector_i_edge *v, i_edge *elements) {
    if(NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_i_edge_pop");
      return out_of_bounds;
    }
    element_i_edge *first = v->head;
    *elements = first->data;
    v->head = first->next;
    v->length--;
    free(first);
    return ok;
}

bool lst_vector_i_edge_is_equal(lst_vector_i_edge *v1, lst_vector_i_edge *v2) {
    if(v1->head == NULL || v2->head == NULL){
      return true;
    }
    int size1 = 0, size2 = 0;
    lst_vector_i_edge_length(v1, &size1);
    lst_vector_i_edge_length(v2, &size2);
    if(size1 != size2){
      return false;
    }
    i_edge tmp1 = {0,0};
    i_edge tmp2 = {0,0};
    for (int i = 0; i < size1; i++){
        lst_vector_i_edge_get(v1, i, &tmp1);
        lst_vector_i_edge_get(v2, i, &tmp2);
        if ((tmp1.p1 != tmp2.p1) || (tmp1.p2 != tmp2.p2)){
          return false;
        }
    }
    return true;
}

error_code print_lst_vector_i_edge (lst_vector_i_edge *v) {
    element_i_edge *tmp = v->head;
    while (tmp != NULL){
        printf("tmp.p1:%d/tmp.p2:%d ", tmp->data.p1, tmp->data.p2);
        tmp = tmp->next;
    }
    return ok;
}

error_code lst_vector_i_edge_set(lst_vector_i_edge *v, int index, i_edge elements) {
    int size = 0;
    lst_vector_i_edge_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_i_edge_set");
      return out_of_bounds;
    }
    int i = 0;
    element_i_edge *tmp = v->head;
    while (i != index){
        i ++;
        tmp = tmp->next;
    }
    tmp->data = elements;
    return ok;
}

error_code lst_vector_i_edge_get(lst_vector_i_edge *v, int index, i_edge *element) {
    int size = 0;
    lst_vector_i_edge_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      printf("index=%d, size=%d",index,size);
      error_code_display(out_of_bounds, "lst_vector_i_edge_get");
      return out_of_bounds;
    }
    int i = 0;
    lst_vector_i_edge tmp = *v;
    while (i != index){
        i ++;
        tmp.head = tmp.head->next;
    }
    *element = tmp.head->data;
    return ok;
}

error_code lst_vector_i_edge_remove(lst_vector_i_edge *v, int index) {
    if (index == 0){
        i_edge none;
        if(lst_vector_i_edge_pop(v, &none) == ok){
          return ok;
        } else {
          error_code_display(out_of_bounds, "lst_vector_i_edge_remove");
          return out_of_bounds;
        }
    }
    int size = 0;
    lst_vector_i_edge_length(v, &size);
    if(index < 0 || index >= size){
      error_code_display(out_of_bounds, "lst_vector_i_edge_remove");
      return out_of_bounds;
    }
    int i = 0;
    element_i_edge *tmp = NULL;
    element_i_edge *elem_replace = v->head;

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

error_code lst_vector_i_edge_insert(lst_vector_i_edge *v, i_edge elements, int index) {
    int size = 0;
    lst_vector_i_edge_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_vector_i_edge_insert");
      return out_of_bounds;
    }
    if(index == 0){
      lst_vector_i_edge_push(v, elements);
    }
    int i = 0;
    element_i_edge *tmp = NULL;
    element_i_edge *elem_replace = v->head;
    element_i_edge *elem = malloc(sizeof(element_i_edge));
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

error_code lst_vector_i_edge_empty(lst_vector_i_edge *v) {
    lst_vector_i_edge_free(v);
    v->length = 0;
    return ok;
}

error_code lst_vector_i_edge_free(lst_vector_i_edge *v) {
    if(v->head == NULL){
      return memory_error;
    }
    i_edge trash;
    while (v->head != NULL){
      lst_vector_i_edge_pop(v, &trash);
    }
    return ok;
}

error_code lst_vector_i_edge_map(lst_vector_i_edge *v, i_edge (*f)(i_edge), lst_vector_i_edge *rhs) {
    lst_vector_i_edge_init(rhs);
    i_edge tmp = {0,0};
    int size = 0;
    lst_vector_i_edge_length(v, &size);
    for (int i = 0; i < size; i++){
      lst_vector_i_edge_push(rhs, tmp);
    }
    for (int i = 0; i < size; i++){
        if (lst_vector_i_edge_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_i_edge_map");
          return memory_error;
        }
        if (lst_vector_i_edge_set(rhs, i, f(tmp)) == memory_error){
          error_code_display(memory_error, "lst_vector_i_edge_map");
          return memory_error;
        }
    }
    return ok;
}

error_code lst_vector_i_edge_filter(lst_vector_i_edge *v, bool (*f)(i_edge), lst_vector_i_edge *rhs) {
    i_edge tmp = {0,0};
    int size = 0;
    lst_vector_i_edge_length(v, &size);
    for (int i = 0; i < size; i++){
        if (lst_vector_i_edge_get(v, i, &tmp) == memory_error){
          error_code_display(memory_error, "lst_vector_i_edge_filter");
          return memory_error;
        }
        if (f(tmp)){
          lst_vector_i_edge_push(rhs, tmp);
        }
    }
    return ok;
}
