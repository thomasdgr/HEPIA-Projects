/**********************************************************************************************************************************************************************************************************************************\
			 ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de tableau 1D pour le stockage de point_2d 
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_2d.h"

error_code vector_2d_init(vector_2d  *v) {
        v->length = 0;
        v->capacity = VECTOR_2D_INIT_CAPACITY;
        v->content = malloc(VECTOR_2D_INIT_CAPACITY * sizeof(point_2d ));
    if(vector_2d_is_valid(*v)){
        return ok;
    }
    error_code_display(memory_error, "vector_2d_init");
    return memory_error;
}

bool vector_2d_is_equal(vector_2d *v1, vector_2d *v2){
    if(vector_2d_is_valid(*v1) && vector_2d_is_valid(*v2) && v1->length == v2->length){
        for (int i = 0; i < v1->length; i++){
            if(v1->content[i].x != v2->content[i].x){
                return false;
           } else if(v1->content[i].y != v2->content[i].y){
               return false;
           }
        }
        return true;
    }
    return false;
}

error_code vector_2d_length(vector_2d *v, int *length) {
    if(vector_2d_is_valid(*v)){
       *length = v->length;
        return ok;
    }
    return vector_2d_default_value(v);
}

error_code vector_2d_push(vector_2d *v, point_2d element) {
    if(vector_2d_is_valid(*v)){
        if (vector_2d_is_full(*v)){
            vector_2d_resize(v, v->capacity * 2);
        }
        v->content[v->length] = element;
        v->length++;
        return ok;
    }
    return vector_2d_default_value(v);
}

error_code vector_2d_pop(vector_2d *v, point_2d *element) {
    if(vector_2d_is_valid(*v)){
        if(v->length > 0){
            *element = v->content[v->length-1];
            v->length--;
            if (v->length < v->capacity / 4){
                vector_2d_resize(v, v->capacity / 2);
            }
            return ok;
        }
        error_code_display(out_of_bounds, "vector_2d_pop");
        return out_of_bounds;
    }
    return vector_2d_default_value(v);
}

error_code vector_2d_set(vector_2d *v, int index, point_2d element) {
    if(vector_2d_is_valid(*v) && index >= 0 && index < v->length){
        v->content[index] = element;
        return ok;
    }
    error_code_display(out_of_bounds, "vector_2d_set");
    return out_of_bounds;
}

error_code vector_2d_get(vector_2d *v, int index, point_2d *element) {
    if(vector_2d_is_valid(*v) && index >= 0){
        if(index < v->length){
            *element = v->content[index];
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_2d_get");
            return out_of_bounds;
        }
    }
    error_code_display(uninitialized, "vector_2d_get");
    return uninitialized;
}

error_code vector_2d_resize(vector_2d *v, int size){
    if(vector_2d_is_valid(*v)){
        v->capacity = size;
        v->content = realloc(v->content, size * sizeof(point_2d));
        return ok;
    }
    return vector_2d_default_value(v);
}

error_code vector_2d_remove(vector_2d *v, int index) {
    if(vector_2d_is_valid(*v) && index >= 0){
        if(v->length > 0){
            for (int i = index; i < v->length; i++){
                v->content[i] = v->content[i+1];
            }
            v->length--;
            return ok;
        }
        error_code_display(out_of_bounds, "vector_2d_remove");
        return out_of_bounds;
    }
    return vector_2d_default_value(v);
}

error_code vector_2d_insert(vector_2d *v, point_2d element, int index) {
    if(vector_2d_is_valid(*v) && index >= 0){
        if(index <= v->length+1){
            for (int i = v->length-1; i >= index; i--){
                if(i+1 >= v->capacity){
                    v->content[i+1] = v->content[i];
                } else {
                    vector_2d_resize(v, v->capacity + 1);
                    v->content[i+1] = v->content[i];
                }
            }
            v->content[index] = element;
            v->length++;
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_2d_insert");
            return out_of_bounds;
        }
    }
    return vector_2d_default_value(v);
}

error_code vector_2d_empty(vector_2d *v) {
    if(vector_2d_is_valid(*v)){
        point_2d p = {0,0};
        while(v->length > 0){
            v->content[v->length-1] = p;
            v->length--;
        }
        return ok;
    }
    return vector_2d_default_value(v);
}

error_code vector_2d_free(vector_2d *v) {
    if(vector_2d_is_valid(*v)){
        v->capacity = 0;
        v->length = 0;
        free(v->content);
        v->content = NULL;
        return ok;
    }
    return vector_2d_default_value(v);
}

point_2d vector_2d_get_last_element(vector_2d v){
    return v.content[v.length-1];
}

bool vector_2d_is_valid(vector_2d v){
    if(v.content != NULL){
        return true;
    } else {
        return false;
    }
}

error_code vector_2d_default_value(vector_2d *v){
    v->content = NULL;
    v->capacity = -1;
    v->length = -1;
    error_code_display(uninitialized, "vector_2d_default_value");
    return uninitialized;
}

bool vector_2d_is_full(vector_2d v){
    if(vector_2d_is_valid(v)){
        return v.capacity == v.length;
    } else{
        return false;
    }
}

bool vector_2d_is_empty(vector_2d v){
    if(vector_2d_is_valid(v)){
        return v.length == 0;
    } else{
        return false;
    }
}

void vector_2d_print_int(vector_2d *v) {
    printf("tab : ");
    for (int i = 0; i < v->length; i++){
        printf(" x: %f - y: %f /",v->content[i].x, v->content[i].y);
    }
    printf("\n");
}

error_code vector_2d_map(vector_2d *v, point_2d(*f)(point_2d ), vector_2d *rhs){
    if(vector_2d_is_valid(*v)){
        if(!vector_2d_is_valid(*rhs)){
            vector_2d_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            vector_2d_push(rhs, (f)(v->content[i]));
        }
        return ok;
  }
  return vector_2d_default_value(v);
}

error_code vector_2d_filter(vector_2d *v, bool(*f)(point_2d ), vector_2d *rhs){
    if(vector_2d_is_valid(*v)){
        if(!vector_2d_is_valid(*rhs)){
            vector_2d_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            if((*f)(v->content[i])){
                vector_2d_push(rhs, v->content[i]);
            }
        }
        return ok;
  }
  return vector_2d_default_value(v);
}
