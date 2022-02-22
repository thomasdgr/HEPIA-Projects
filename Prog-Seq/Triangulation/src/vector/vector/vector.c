/**********************************************************************************************************************************************************************************************************************************\
			 ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de tableaux 1D pour le stockage de int (définit comme "type") 
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector.h"

error_code vector_init(vector *v) {
        v->length = 0;
        v->capacity = VECTOR_INIT_CAPACITY;
        v->content = malloc(VECTOR_INIT_CAPACITY * sizeof(type));
    if(vector_is_valid(*v)){
        return ok;
    }
    return memory_error;
}

bool vector_is_equal(vector *v1, vector *v2){
    if(vector_is_valid(*v1) && vector_is_valid(*v2) && v1->length == v2->length){
        for (int i = 0; i < v1->length; i++){
            if(v1->content[i] != v2->content[i]){
                return false;
           }
        }
        return true;
    }
    return false;
}

error_code vector_length(vector *v, int *length) {
    if(vector_is_valid(*v)){
       *length = v->length;
        return ok;
    }
    return vector_default_value(v);
}

error_code vector_push(vector *v, type element) {
    if(vector_is_valid(*v)){
        if (vector_is_full(*v)){
            vector_resize(v, v->capacity * 2);
        }
        v->content[v->length] = element;
        v->length++;
        return ok;
    }
    return vector_default_value(v);
}

error_code vector_pop(vector *v, type *element) {
    if(vector_is_valid(*v)){
        if(v->length > 0){
            *element = v->content[v->length-1];
            v->length--;
            v->content[v->length] = 0;
            if (v->length < v->capacity / 4){
                vector_resize(v, v->capacity / 2);
            }
            return ok;
        }
        return out_of_bounds;
    }
    return vector_default_value(v);
}

error_code vector_set(vector *v, int index, type element) {
    if(vector_is_valid(*v) && index >= 0 && index < v->length){
        v->content[index] = element;
        return ok;
    }
    return out_of_bounds;
}

error_code vector_get(vector *v, int index, type *element) {
    if(vector_is_valid(*v) && index >= 0){
        if(index < v->length){
            *element = v->content[index];
            return ok;
        } else {
            return out_of_bounds;
        }
    }
    return uninitialized;
}

error_code vector_resize(vector *v, int size){
    if(vector_is_valid(*v)){
        v->capacity = size;
        v->content = realloc(v->content, size * sizeof(type));
        return ok;
    }
    return vector_default_value(v);
}

error_code vector_remove(vector *v, int index) {
    if(vector_is_valid(*v) && index >= 0){
        if(v->length > 0){
            for (int i = index; i < v->length; i++){
                v->content[i] = v->content[i+1];
            }
            v->content[v->length] = 0;
            v->length--;
            return ok;
        }
        return out_of_bounds;
    }
    return vector_default_value(v);
}

error_code vector_insert(vector *v, type element, int index) {
    if(vector_is_valid(*v) && index >= 0){
        if(index <= v->length+1){
            for (int i = v->length-1; i >= index; i--){
                if(i+1 >= v->capacity){
                    v->content[i+1] = v->content[i];
                } else {
                    vector_resize(v, v->capacity + 1);
                    v->content[i+1] = v->content[i];
                }
            }
            v->content[index] = element;
            v->length++;
            return ok;
        } else {
            return out_of_bounds;
        }
    }
    return vector_default_value(v);
}

error_code vector_empty(vector *v) {
    if(vector_is_valid(*v)){
        while(v->length > 0){
            v->content[v->length-1] = 0;
            v->length--;
        }
        return ok;
    }
    return vector_default_value(v);
}

error_code vector_free(vector *v) {
    if(vector_is_valid(*v)){
        v->capacity = 0;
        v->length = 0;
        free(v->content);
        v->content = NULL;
        return ok;
    }
    return vector_default_value(v);
}

type vector_get_last_element(vector v){
    return v.content[v.length-1];
}

bool vector_is_valid(vector v){
    if(v.content != NULL){
        return true;
    } else {
        return false;
    }
}

error_code vector_default_value(vector *v){
    v->content = NULL;
    v->capacity = -1;
    v->length = -1;
    return uninitialized;
}

bool vector_is_full(vector v){
    if(vector_is_valid(v)){
        return v.capacity == v.length;
    } else{
        return false;
    }
}

bool vector_is_empty(vector v){
    if(vector_is_valid(v)){
        return v.length == 0;
    } else{
        return false;
    }
}

void vector_print_int(vector *v) {
    printf("vector : ");
    for (int i = 0; i < v->length; i++){
        printf(" %d /",v->content[i]);
    }
    printf("\n");
}

error_code vector_map(vector *v, type  (*f)(type), vector *rhs) {
    if(vector_is_valid(*v)){
        if(!vector_is_valid(*rhs)){
            vector_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            vector_push(rhs, (f)(v->content[i]));
        }
        return ok;
  }
  return vector_default_value(v);
}

error_code vector_filter(vector *v, bool  (*f)(type), vector *rhs) {
    if(vector_is_valid(*v)){
        if(!vector_is_valid(*rhs)){
            vector_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            if((*f)(v->content[i])){
                vector_push(rhs, v->content[i]);
            }
        }
        return ok;
  }
  return vector_default_value(v);
}
