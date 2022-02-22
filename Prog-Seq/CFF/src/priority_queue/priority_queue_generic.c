/*******************************************************************************
			       ____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour stocker des données génériques
(___) \.  _.\__. `\___           |    dans une file de priorité en utilisant une  
(___)  )\/  \_____/  ~\.         |    fonction de comparaison pour trier les données
(___) . \   `         `\         |   
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	03/06/2020

\******************************************************************************/
#include "priority_queue_generic.h"

error_code priority_queue_generic_init(priority_queue_generic *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code priority_queue_generic_push(priority_queue_generic *v, void* elements, bool (*f)(void*, void*)) {
    g_element* crt;
    crt = v->head;
    g_element* tmp = crt;
    g_element *new = malloc(sizeof(g_element));
    new->data = elements;
    new->next = NULL;
    if(priority_queue_generic_is_empty(v)){
      v->head = new;
    } 
    while(crt !=NULL){
      if (f(new->data, crt->data)){
        new->next = crt;
        if(v->head == crt){
          v->head = new;
          break;
        } else {
          tmp->next = new;
          break;
        }
      }
      else if(crt->next == NULL){
        crt->next = new;
        break;
      }
      tmp = crt;
      crt = crt->next;
    }
    v->length++;
    return ok;
}

error_code priority_queue_generic_pop(priority_queue_generic *v, void** elements) {
  if(NULL == v->head){
    error_code_display(out_of_bounds, "priority_queue_generic_pop");
    return out_of_bounds;
  }
  g_element *elem = v->head;
  *elements = elem->data;
  v->head = elem->next;
  v->length--;
  free(elem);
  return ok;
}

error_code priority_queue_generic_peek(priority_queue_generic *v, void** elements){
  if(NULL == v->head){
    error_code_display(out_of_bounds, "priority_queue_generic_peek");
    return out_of_bounds;
  }
  *elements = v->head->data;
  return ok;
}

error_code priority_queue_generic_empty(priority_queue_generic *v) {
    priority_queue_generic_free(v);
    v->length = 0;
    return ok;
}

bool priority_queue_generic_is_empty(priority_queue_generic *v) {
    return v->head == NULL;
}

void priority_queue_generic_print_int(priority_queue_generic *v) {
    g_element *tmp = v->head;
    while (tmp != NULL){
      void * data = tmp->data;
        printf(" %d ", *(int*)data);
        tmp = tmp->next;
    }
    printf("\n");
}

error_code priority_queue_generic_free(priority_queue_generic *v) {
    if(v->head == NULL){
      return memory_error;
    }
    int a = 0;
    void* trash = &a;
    while (v->head != NULL){
      priority_queue_generic_pop(v, &trash);
    }
    return ok;
}

bool cmp_generic(void* i, void* j){
  return i>j;
}