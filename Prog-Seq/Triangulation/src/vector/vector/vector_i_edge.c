/**********************************************************************************************************************************************************************************************************************************\
			 ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de tableaux 1D pour le stockage de i_edge
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_i_edge.h"

error_code vector_i_edge_init(vector_i_edge *v) {
        v->length = 0;
        v->capacity = VECTOR_I_EDGE_INIT_CAPACITY;
        v->content = malloc(VECTOR_I_EDGE_INIT_CAPACITY * sizeof(i_edge));
    if(vector_i_edge_is_valid(*v)){
        return ok;
    }
    error_code_display(memory_error, "vector_i_edge_init");
    return memory_error;
}

bool vector_i_edge_is_equal(vector_i_edge *v1, vector_i_edge *v2){
    if(vector_i_edge_is_valid(*v1) && vector_i_edge_is_valid(*v2) && v1->length == v2->length){
        for (int i = 0; i < v1->length; i++){
            if(v1->content[i].p1 != v2->content[i].p1){
                return false;
           } else if(v1->content[i].p2 != v2->content[i].p2){
                return false;
           }
        }
        return true;
    }
    return false;
}

error_code vector_i_edge_length(vector_i_edge *v, int *length) {
    if(vector_i_edge_is_valid(*v)){
       *length = v->length;
        return ok;
    }
    return vector_i_edge_default_value(v);
}

error_code vector_i_edge_push(vector_i_edge *v, i_edge element) {
    if(vector_i_edge_is_valid(*v)){
        if (vector_i_edge_is_full(*v)){
            vector_i_edge_resize(v, v->capacity * 2);
        }
        v->content[v->length] = element;
        v->length++;
        return ok;
    }
    return vector_i_edge_default_value(v);
}

error_code vector_i_edge_pop(vector_i_edge *v, i_edge *element) {
    if(vector_i_edge_is_valid(*v)){
        if(v->length > 0){
            *element = v->content[v->length-1];
            v->length--;
            if (v->length < v->capacity / 4){
                vector_i_edge_resize(v, v->capacity / 2);
            }
            return ok;
        }
        error_code_display(out_of_bounds, "vector_i_edge_pop");
        return out_of_bounds;
    }
    return vector_i_edge_default_value(v);
}

error_code vector_i_edge_set(vector_i_edge *v, int index, i_edge element) {
    if(vector_i_edge_is_valid(*v) && index >= 0 && index < v->length){
        v->content[index] = element;
        return ok;
    }
    error_code_display(out_of_bounds, "vector_i_edge_set");
    return out_of_bounds;
}

error_code vector_i_edge_get(vector_i_edge *v, int index, i_edge *element) {
    if(vector_i_edge_is_valid(*v) && index >= 0){
        if(index < v->length){
            *element = v->content[index];
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_i_edge_get");
            return out_of_bounds;
        }
    }
    error_code_display(uninitialized, "vector_i_edge_get");
    return uninitialized;
}

error_code vector_i_edge_resize(vector_i_edge *v, int size){
    if(vector_i_edge_is_valid(*v)){
        v->capacity = size;
        v->content = realloc(v->content, size * sizeof(i_edge));
        return ok;
    }
    return vector_i_edge_default_value(v);
}

error_code vector_i_edge_remove(vector_i_edge *v, int index) {
    if(vector_i_edge_is_valid(*v) && index >= 0){
        if(v->length > 0){
            for (int i = index; i < v->length; i++){
                v->content[i] = v->content[i+1];
            }
            v->length--;
            return ok;
        }
        error_code_display(out_of_bounds, "vector_i_edge_remove");
        return out_of_bounds;
    }
    return vector_i_edge_default_value(v);
}

error_code vector_i_edge_insert(vector_i_edge *v, i_edge element, int index) {
    if(vector_i_edge_is_valid(*v) && index >= 0){
        if(index <= v->length+1){
            for (int i = v->length-1; i >= index; i--){
                if(i+1 >= v->capacity){
                    v->content[i+1] = v->content[i];
                } else {
                    vector_i_edge_resize(v, v->capacity + 1);
                    v->content[i+1] = v->content[i];
                }
            }
            v->content[index] = element;
            v->length++;
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_i_edge_insert");
            return out_of_bounds;
        }
    }
    return vector_i_edge_default_value(v);
}

error_code vector_i_edge_empty(vector_i_edge *v) {
    if(vector_i_edge_is_valid(*v)){
        i_edge e = {0,0};
        while(v->length > 0){
            v->content[v->length-1] = e;
            v->length--;
        }
        return ok;
    }
    return vector_i_edge_default_value(v);
}

error_code vector_i_edge_free(vector_i_edge *v) {
    if(vector_i_edge_is_valid(*v)){
        v->capacity = 0;
        v->length = 0;
        free(v->content);
        v->content = NULL;
        return ok;
    }
    return vector_i_edge_default_value(v);
}

i_edge vector_i_edge_get_last_element(vector_i_edge v){
    return v.content[v.length-1];
}

bool vector_i_edge_is_valid(vector_i_edge v){
    if(v.content != NULL){
        return true;
    } else {
        return false;
    }
}

error_code vector_i_edge_default_value(vector_i_edge *v){
    v->content = NULL;
    v->capacity = -1;
    v->length = -1;
    error_code_display(uninitialized, "vector_i_edge_default_value");
    return uninitialized;
}

bool vector_i_edge_is_full(vector_i_edge v){
    if(vector_i_edge_is_valid(v)){
        return v.capacity == v.length;
    } else{
        return false;
    }
}

bool vector_i_edge_is_empty(vector_i_edge v){
    if(vector_i_edge_is_valid(v)){
        return v.length == 0;
    } else{
        return false;
    }
}

void vector_i_edge_print_int(vector_i_edge *v) {
    printf("tab : ");
    for (int i = 0; i < v->length; i++){
        printf(" p1: %d - p2: %d /",v->content[i].p1, v->content[i].p2);
    }
    printf("\n");
}

error_code vector_i_edge_map(vector_i_edge *v, i_edge(*f)(i_edge), vector_i_edge *rhs) {
    if(vector_i_edge_is_valid(*v)){
        if(!vector_i_edge_is_valid(*rhs)){
            vector_i_edge_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            vector_i_edge_push(rhs, (f)(v->content[i]));
        }
        return ok;
  }
  return vector_i_edge_default_value(v);
}

error_code vector_i_edge_filter(vector_i_edge *v, bool(*f)(i_edge), vector_i_edge *rhs) {
    if(vector_i_edge_is_valid(*v)){
        if(!vector_i_edge_is_valid(*rhs)){
            vector_i_edge_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            if((*f)(v->content[i])){
                vector_i_edge_push(rhs, v->content[i]);
            }
        }
        return ok;
  }
  return vector_i_edge_default_value(v);
}
