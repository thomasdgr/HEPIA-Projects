/**********************************************************************************************************************************************************************************************************************************\
			 ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de tableaux 1D pour le stockage de i_triangles 
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_i_triangle.h"

error_code vector_i_triangle_init(vector_i_triangle *v) {
        v->length = 0;
        v->capacity = VECTOR_I_TRIANGLE_INIT_CAPACITY;
        v->content = malloc(VECTOR_I_TRIANGLE_INIT_CAPACITY * sizeof(i_triangle));
    if(vector_i_triangle_is_valid(*v)){
        return ok;
    }
    error_code_display(memory_error, "vector_i_triangle_init");
    return memory_error;
}

bool vector_i_triangle_is_equal(vector_i_triangle *v1, vector_i_triangle *v2){
    if(vector_i_triangle_is_valid(*v1) && vector_i_triangle_is_valid(*v2) && v1->length == v2->length){
        for (int i = 0; i < v1->length; i++){
            if(v1->content[i].p1 != v2->content[i].p1){
                return false;
           } else if(v1->content[i].p2 != v2->content[i].p2){
                return false;
           } else if(v1->content[i].p3 != v2->content[i].p3){
                return false;
           }
        }
        return true;
    }
    return false;
}

error_code vector_i_triangle_length(vector_i_triangle *v, int *length) {
    if(vector_i_triangle_is_valid(*v)){
       *length = v->length;
        return ok;
    }
    return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_push(vector_i_triangle *v, i_triangle element) {
    if(vector_i_triangle_is_valid(*v)){
        if (vector_i_triangle_is_full(*v)){
            vector_i_triangle_resize(v, v->capacity * 2);
        }
        v->content[v->length] = element;
        v->length++;
        return ok;
    }
    return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_pop(vector_i_triangle *v, i_triangle *element) {
    if(vector_i_triangle_is_valid(*v)){
        if(v->length > 0){
            *element = v->content[v->length-1];
            v->length--;
            if (v->length < v->capacity / 4){
                vector_i_triangle_resize(v, v->capacity / 2);
            }
            return ok;
        }
        error_code_display(out_of_bounds, "vector_i_triangle_pop");
        return out_of_bounds;
    }
    return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_set(vector_i_triangle *v, int index, i_triangle element) {
    if(vector_i_triangle_is_valid(*v) && index >= 0 && index < v->length){
        v->content[index] = element;
        return ok;
    }
    error_code_display(out_of_bounds, "vector_i_triangle_set");
    return out_of_bounds;
}

error_code vector_i_triangle_get(vector_i_triangle *v, int index, i_triangle *element) {
    if(vector_i_triangle_is_valid(*v) && index >= 0){
        if(index < v->length){
            *element = v->content[index];
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_i_triangle_get");
            return out_of_bounds;
        }
    }
    error_code_display(uninitialized, "vector_i_triangle_get");
    return uninitialized;
}

error_code vector_i_triangle_resize(vector_i_triangle *v, int size){
    if(vector_i_triangle_is_valid(*v)){
        v->capacity = size;
        v->content = realloc(v->content, size * sizeof(i_triangle));
        return ok;
    }
    return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_remove(vector_i_triangle *v, int index) {
    if(vector_i_triangle_is_valid(*v) && index >= 0){
        if(v->length > 0 && index < v->length){
            for (int i = index; i < (v->length-1); i++){
                v->content[i] = v->content[i+1];
            }
            v->length--;
            return ok;
        }
        error_code_display(out_of_bounds, "vector_i_triangle_remove");
        return out_of_bounds;
    }
    return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_insert(vector_i_triangle *v, i_triangle element, int index) {
    if(vector_i_triangle_is_valid(*v) && index >= 0){
        if(index <= v->length+1){
            for (int i = v->length-1; i >= index; i--){
                if(i+1 >= v->capacity){
                    v->content[i+1] = v->content[i];
                } else {
                    vector_i_triangle_resize(v, v->capacity + 1);
                    v->content[i+1] = v->content[i];
                }
            }
            v->content[index] = element;
            v->length++;
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_i_triangle_insert");
            return out_of_bounds;
        }
    }
    return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_empty(vector_i_triangle *v) {
    if(vector_i_triangle_is_valid(*v)){
        i_triangle t = {0,0,0};
        while(v->length > 0){
            v->content[v->length-1] = t;
            v->length--;
        }
        return ok;
    }
    return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_free(vector_i_triangle *v) {
    if(vector_i_triangle_is_valid(*v)){
        v->capacity = 0;
        v->length = 0;
        free(v->content);
        v->content = NULL;
        return ok;
    }
    return vector_i_triangle_default_value(v);
}

i_triangle vector_i_triangle_get_last_element(vector_i_triangle v){
    return v.content[v.length-1];
}

bool vector_i_triangle_is_valid(vector_i_triangle v){
    return v.content != NULL;
}

error_code vector_i_triangle_default_value(vector_i_triangle *v){
    v->content = NULL;
    v->capacity = -1;
    v->length = -1;
    error_code_display(uninitialized, "vector_i_triangle_defalut_value");
    return uninitialized;
}

bool vector_i_triangle_is_full(vector_i_triangle v){
    if(vector_i_triangle_is_valid(v)){
        return v.capacity == v.length;
    } else{
        return false;
    }
}

bool vector_i_triangle_is_empty(vector_i_triangle v){
    if(vector_i_triangle_is_valid(v)){
        return v.length == 0;
    } else{
        return false;
    }
}

void vector_i_triangle_print_int(vector_i_triangle *v) {
    printf("tab : ");
    for (int i = 0; i < v->length; i++){
        printf(" p1: %d - p2: %d - p3: %d /",v->content[i].p1, v->content[i].p2, v->content[i].p3);
    }
    printf("\n");
}

error_code vector_i_triangle_map(vector_i_triangle *v, i_triangle  (*f)(i_triangle), vector_i_triangle *rhs) {
    if(vector_i_triangle_is_valid(*v)){
        if(!vector_i_triangle_is_valid(*rhs)){
            vector_i_triangle_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            vector_i_triangle_push(rhs, (f)(v->content[i]));
        }
        return ok;
  }
  return vector_i_triangle_default_value(v);
}

error_code vector_i_triangle_filter(vector_i_triangle *v, bool  (*f)(i_triangle), vector_i_triangle *rhs) {
    if(vector_i_triangle_is_valid(*v)){
        if(!vector_i_triangle_is_valid(*rhs)){
            vector_i_triangle_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            if((*f)(v->content[i])){
                vector_i_triangle_push(rhs, v->content[i]);
            }
        }
        return ok;
  }
  return vector_i_triangle_default_value(v);
}
