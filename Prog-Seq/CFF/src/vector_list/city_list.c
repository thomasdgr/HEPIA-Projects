/*******************************************************************************
			       ____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour stocker des villes dans
(___) \.  _.\__. `\___           |    une liste specifique
(___)  )\/  \_____/  ~\.         |    
(___) . \   `         `\         |   
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	03/06/2020

\******************************************************************************/
#include "city_list.h"

error_code lst_city_init(lst_city *v) {
    v->head = NULL;
    v->length = 0;
    return ok;
}

error_code lst_city_length(lst_city *v, int *length) {
    *length = v->length;
    return ok;
}

error_code lst_city_push(lst_city *v, city *elements) {
    city *alo = malloc(sizeof(city));
    strncpy(alo->name, elements->name, NAME_LEN-1);
    alo->longitude = elements->longitude;
    alo->latitude = elements->latitude;
    alo->next = NULL;
    if(v->length == 0){
      v->head = alo;
    } else {
      city *elem = v->head;
      while(elem != NULL){
        if(elem->next == NULL){
          break;
        } else{
          elem = elem->next;
        }
      }
      elem->next = alo;
    }
    v->length++;
    return ok;
}

error_code print_lst_city (lst_city *v) {
    city *tmp = v->head;
    int i = 0;
    while (tmp != NULL){
      int count = 0;
        char* text = tmp->name; 
        for(int j = 0; text[j]; j++){
          if(text[j] != ' '){
            text[count++] = text[j];
          }
        }
        text[count] = '\0';
        printf("[%d:%s] ",i, text);
        i++;
        tmp = tmp->next;
    }
    printf("\n");
    return ok;
}

error_code lst_city_pop(lst_city *v, city *elements) {
    if(NULL == v->head){
      error_code_display(out_of_bounds, "lst_city_pop");
      return out_of_bounds;
    }
    city *first = v->head;
    *elements = *first;
    v->head = first->next;
    v->length--;
    free(first);
    return ok;
}


error_code lst_city_set(lst_city *v, int index, city *elements) {
    int size = 0;
    lst_city_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_city_set");
      return out_of_bounds;
    }
    int i = 0;
    city *tmp = v->head;
    while (i != index){
        i ++;
        tmp = tmp->next;
    }
    tmp = elements;
    return ok;
}

error_code lst_city_get(lst_city *v, int index, city *element) {
    int size = 0;
    lst_city_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_city_get");
      return out_of_bounds;
    }
    int i = 0;
    lst_city tmp = *v;
    while (i != index){
        i ++;
        tmp.head = tmp.head->next;
    }
    *element = *tmp.head;
    return ok;
}

error_code lst_city_remove(lst_city *v, int index) {
    if (index == 0){
        city none;
        if(lst_city_pop(v, &none) == ok){
          return ok;
        } else {
          error_code_display(out_of_bounds, "lst_city_remove");
          return out_of_bounds;
        }
    }
    int size = 0;
    lst_city_length(v, &size);
    if(index < 0 || index >= size){
      error_code_display(out_of_bounds, "lst_city_remove");
      return out_of_bounds;
    }
    int i = 0;
    city *tmp = NULL;
    city *elem_replace = v->head;

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

error_code lst_city_insert(lst_city *v, city *elements, int index) {
    int size = 0;
    lst_city_length(v, &size);
    if(index < 0 || index > size || NULL == v->head){
      error_code_display(out_of_bounds, "lst_city_insert");
      return out_of_bounds;
    }
    if(index == 0){
      lst_city_push(v, elements);
    }
    int i = 0;
    city *tmp = NULL;
    city *elem_replace = v->head;
    city *elem = malloc(sizeof(city));
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

error_code lst_city_empty(lst_city *v) {
    lst_city_free(v);
    v->length = 0;
    return ok;
}

error_code lst_city_free(lst_city *v) {
    if(v->head== NULL){
      return memory_error;
    }
    city trash;
    while (v->head!= NULL){
      lst_city_pop(v, &trash);
    }
    return ok;
}

char* get_city_from_index(int index){
  if(index == 0)return "Geneve";
  if(index == 1)return "Lausanne";
  if(index == 2)return "Neuchatel";
  if(index == 3)return "Delemont";
  if(index == 4)return "Bale";
  if(index == 5)return "Berne";
  if(index == 6)return "Lucerne";
  if(index == 7)return "Zurich";
  if(index == 8)return "Schaffouse";
  if(index == 9)return "St.-Gall";
  if(index == 10)return "Coire";
  if(index == 11)return "St.-Moritz";
  if(index == 12)return "Bellinzone";
  if(index == 13)return "Andermatt";
  if(index == 14)return "Sion";
  else return "c'est facheux...";
}

int get_index_from_city(char* city){
  if(strcmp(city, "Geneve") == 0)return 0;
  if(strcmp(city, "Lausanne") == 0)return 1;
  if(strcmp(city, "Neuchatel") == 0)return 2;
  if(strcmp(city, "Delemont") == 0)return 3;
  if(strcmp(city, "Bale") == 0)return 4;
  if(strcmp(city, "Berne") == 0)return 5;
  if(strcmp(city, "Lucerne") == 0)return 6;
  if(strcmp(city, "Zurich") == 0)return 7;
  if(strcmp(city, "Schaffouse") == 0)return 8;
  if(strcmp(city, "St.-Gall") == 0)return 9;
  if(strcmp(city, "Coire") == 0)return 10;
  if(strcmp(city, "St.-Moritz") == 0)return 11;
  if(strcmp(city, "Bellinzone") == 0)return 12;
  if(strcmp(city, "Andermatt") == 0)return 13;
  if(strcmp(city, "Sion") == 0)return 14;
  else return -1;
}