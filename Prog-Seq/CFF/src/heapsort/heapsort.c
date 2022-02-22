/*******************************************************************************
			____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : librairie de fonctions
 __/  |    | \__/|               |    utilisées pour stocker des elements int
(___) \.  _.\__. `\___           |    dans une structure utilisant un heapsort 
(___)  )\/  \_____/  ~\.         |    pour trier les données
(___) . \   `         `\         |   
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	03/06/2020

\******************************************************************************/
#include "heapsort.h"

// code du heapsort 

void print_tab(int size, int tab[size]){
    for(int i=0; i<size;i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}

int trouver_fils_gauche(int i){
    return i*2 +1;
}

int trouver_fils_droit(int i){
    return i*2 +2;
}

void swap(int * a, int * b){
    if(a != NULL && b != NULL && a != b){
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

int max3(int size, int tab[size], int i){
    int left = trouver_fils_gauche(i);
    int right = trouver_fils_droit(i);
    int max = i;
    if(right < size && left < size){
        if(tab[right] >= tab[left]){
            max = right;
        }
        if(tab[left] >= tab[right]){
            max = left;
        }
        if(tab[max] <= tab[i]){
            max = i;
        }
    } else if(left < size){
        if(tab[left] > tab[max]){
            max = left;
        }
    }
    return max;
}

void promotion(int size, int tab[size],int i){
    int max = max3(size, tab, i);
    if(i != max){
      swap(&tab[max], &tab[i]);
      promotion(size, tab, max);
    }
}

void entassement(int size, int tab[size]){
  for(int i = (size/2)-1; i >= 0; i--){
    promotion(size, tab, i);
  }
}

void heapsort(int size, int tab[size]){
  entassement(size, tab);
  int count = size-1;
  swap(&tab[0], &tab[size-1]);
  while(count > 1){
    promotion(count, tab, 0);
    swap(&tab[0], &tab[count-1]);
    count--;
  }
}

// code pour la structure hpq qui utilise le heapsort

error_code hpq_init(hpq *v) {
        v->length = 0;
        v->capacity = INIT_CAPACITY;
        v->data = malloc(INIT_CAPACITY * sizeof(int));
    if(hpq_is_valid(*v)){
        return ok;
    }
    return memory_error;
}

error_code hpq_peek(hpq *v, int *elements){
  if(NULL == v){
    error_code_display(out_of_bounds, "priority_queue_peek");
    return out_of_bounds;
  }
  *elements = v->data[v->length-1];
  return ok;
}

error_code hpq_push(hpq *v, int element) {
    if(hpq_is_valid(*v)){
        if (hpq_is_full(*v)){
            hpq_resize(v, v->capacity * 2);
        }
        v->data[v->length] = element;
        v->length++;
        return ok;
    }
    return hpq_default_value(v);
}

error_code hpq_pop(hpq *v, int *element) {
    if(hpq_is_valid(*v)){
        if(v->length > 0){
            *element = v->data[v->length-1];
            v->length--;
            v->data[v->length] = 0;
            if (v->length < v->capacity / 4){
                hpq_resize(v, v->capacity / 2);
            }
            return ok;
        }
        return out_of_bounds;
    }
    return hpq_default_value(v);
}

error_code hpq_resize(hpq *v, int size){
    if(hpq_is_valid(*v)){
        v->capacity = size;
        v->data = realloc(v->data, size * sizeof(int));
        return ok;
    }
    return hpq_default_value(v);
}

error_code hpq_empty(hpq *v) {
    if(hpq_is_valid(*v)){
        while(v->length > 0){
            v->data[v->length-1] = 0;
            v->length--;
        }
        return ok;
    }
    return hpq_default_value(v);
}

error_code hpq_free(hpq *v) {
    if(hpq_is_valid(*v)){
        v->capacity = 0;
        v->length = 0;
        free(v->data);
        v->data = NULL;
        return ok;
    }
    return hpq_default_value(v);
}

bool hpq_is_valid(hpq v){
    return v.data != NULL;
}

error_code hpq_default_value(hpq *v){
    v->data = NULL;
    v->capacity = -1;
    v->length = -1;
    return uninitialized;
}

bool hpq_is_full(hpq v){
    if(hpq_is_valid(v)){
        return v.capacity == v.length;
    } else{
        return false;
    }
}

bool hpq_is_empty(hpq v){
    if(hpq_is_valid(v)){
        return v.length == 0;
    } else{
        return false;
    }
}

void hpq_print_int(hpq *v) {
    for (int i = 0; i < v->length; i++){
        printf(" %d /",v->data[i]);
    }
    printf("\n");
}