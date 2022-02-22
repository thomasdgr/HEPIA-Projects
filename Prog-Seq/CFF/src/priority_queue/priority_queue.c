/*******************************************************************************
			       ____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour stocker des données int
(___) \.  _.\__. `\___           |    dans une file de priorité en utilisant une  
(___)  )\/  \_____/  ~\.         |    fonction de comparaison pour trier les données
(___) . \   `         `\         |   
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	03/06/2020

\******************************************************************************/

#include "priority_queue.h"

error_code priority_queue_init(priority_queue *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code priority_queue_push(priority_queue *v, int elements, bool (* f)(int, int)){
    element* crt;
    crt = v->head;
    element* tmp = crt;
    element *new = malloc(sizeof(element));
    new->data = elements;
    new->next = NULL;
    if(priority_queue_is_empty(v)){
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

error_code priority_queue_pop(priority_queue *v, int *elements) {
  if(NULL == v->head){
    error_code_display(out_of_bounds, "priority_queue_pop");
    return out_of_bounds;
  }
  element *first = v->head;
  *elements = first->data;
  v->head = first->next;
  v->length--;
  free(first);
  return ok;
}

error_code priority_queue_peek(priority_queue *v, int *elements){
  if(NULL == v->head){
    error_code_display(out_of_bounds, "priority_queue_peek");
    return out_of_bounds;
  }
  *elements = v->head->data;
  return ok;
}

void priority_queue_print_int(priority_queue *v) {
    element *tmp = v->head;
    while (tmp != NULL){
        printf(" %d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

error_code priority_queue_empty(priority_queue *v) {
    priority_queue_free(v);
    v->length = 0;
    return ok;
}

bool priority_queue_is_empty(priority_queue *v) {
    return v->head == NULL;
}

error_code priority_queue_free(priority_queue *v) {
    if(v->head == NULL){
      return memory_error;
    }
    int trash;
    while (v->head != NULL){
      priority_queue_pop(v, &trash);
    }
    return ok;
}

bool cmp(int i, int j){
  return i>j;
}