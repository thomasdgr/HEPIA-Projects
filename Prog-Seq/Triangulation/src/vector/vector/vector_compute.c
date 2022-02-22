/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de mini-tests pour les listes chainées et
 __/  |    | \__/|               |                 les tableaux de int (définit comme "type")
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
//#include "vector.h"
#include "vector_list.h"

int lst_print_vector(lst_vector v){
    printf("tab : ");
    lst_vector tmp = v;
    for (int i = 0; i < v->length; i++){
      printf(" %d /",tmp.data);
    }
    printf("\n");
    return 1;
}

type lst_add1(type n){
  n +=1;
  return n;
}

int main(){
    // test de la fonction init  et resize : ok
    lst_vector victor;
    lst_vector_init(&victor);

    printf("\ntest de la fonction push : ok\n");
    lst_vector_push(&victor, 2);
    lst_vector_push(&victor, 3);
    lst_vector_push(&victor, 4);
    lst_vector_push(&victor, 1);
    lst_vector_push(&victor, 5);
    lst_vector_push(&victor, 6);
    lst_vector_push(&victor, 7);
    lst_vector_push(&victor, 8);
    lst_vector_push(&victor, 9);
    lst_vector_push(&victor, 10);
    lst_vector_push(&victor, 11);
    printf("\n");

    printf("test de la fonction insert : ok\n");
    lst_vector_insert(&victor, 10, 2);
    lst_print_vector(victor);
    printf("\n");

    printf("test de la fonction length : ok\n");
    int *length = malloc(sizeof(type));
    lst_vector_length(&victor, length);
    printf("value : %d\n", *length);
    printf("\n");

    // remplacer la valeur ? si oui, par un 0 ?
    printf("test de la fonction pop : ok\n");
    type *value = malloc(sizeof(type));
    lst_vector_pop(&victor, value);
    lst_print_vector(victor);
    printf("value : %d\n", *value);
    printf("\n");

    printf("test de la fonction remove : ok\n");
    lst_vector_remove(&victor, 3);
    lst_print_vector(victor);
    printf("\n");

    printf("test de la fonction set : ok\n");
    int value_set = 0;
    value_set = lst_vector_set(&victor, 2, value_set);
    printf("value : %d\n", value_set);
    printf("\n");

    printf("test de la fonction get : ok\n");
    type *value_get = malloc(sizeof(type));
    lst_vector_get(&victor, 2,   value_get);
    lst_print_vector(victor);
    printf("value : %d\n", *value_get);
    printf("\n");

    printf("test de la fonction empty : ok\n");
    lst_vector_empty(&victor);
    lst_print_vector(victor);
    printf("\n");

    printf("test de la fonction map : pas fait\n");
    lst_vector rhs;
    type *n = malloc(sizeof(type));
    lst_vector_init(rhs);
    lst_vector_map(&victor, add1(n), &rhs);
    printf("\n");

    printf("test de la fonction filter: pas fait\n");
    printf("\n");

    printf("test de la fonction free : ok\n");
    lst_vector_free(&victor);
    lst_vector_free(&rhs);
    free(value);
    free(n);
    free(length);
    free(value_get);
    printf("\n");

    return 0;
}
