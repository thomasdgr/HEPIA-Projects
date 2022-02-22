/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Librairie de tableaux 1D pour le stockage de point_3d 
 __/  |    | \__/|               |
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "vector_3d.h"

error_code vector_3d_init(vector_3d  *v) {
        v->length = 0;
        v->capacity = VECTOR_3D_INIT_CAPACITY;
        v->content = malloc(VECTOR_3D_INIT_CAPACITY * sizeof(point_3d));
    if(vector_3d_is_valid(*v)){
        return ok;
    }
    error_code_display(memory_error, "vector_3d_init");
    return memory_error;
}

bool vector_3d_is_equal(vector_3d *v1, vector_3d *v2){
    if(vector_3d_is_valid(*v1) && vector_3d_is_valid(*v2) && v1->length == v2->length){
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

error_code vector_3d_length(vector_3d *v, int *length) {
    if(vector_3d_is_valid(*v)){
       *length = v->length;
        return ok;
    }
    return vector_3d_default_value(v);
}

error_code vector_3d_push(vector_3d *v, point_3d element) {
    if(vector_3d_is_valid(*v)){
        if (vector_3d_is_full(*v)){
            vector_3d_resize(v, v->capacity * 2);
        }
        v->content[v->length] = element;
        v->length++;
        return ok;
    }
    return vector_3d_default_value(v);
}

error_code vector_3d_pop(vector_3d *v, point_3d *element) {
    if(vector_3d_is_valid(*v)){
        if(v->length > 0){
            *element = v->content[v->length-1];
            v->length--;
            if (v->length < v->capacity / 4){
                vector_3d_resize(v, v->capacity / 2);
            }
            return ok;
        }
        error_code_display(out_of_bounds, "vector_3d_pop");
        return out_of_bounds;
    }
    return vector_3d_default_value(v);
}

error_code vector_3d_set(vector_3d *v, int index, point_3d element) {
    if(vector_3d_is_valid(*v) && index >= 0 && index < v->length){
        v->content[index] = element;
        return ok;
    }
    error_code_display(out_of_bounds, "vector_3d_set");
    return out_of_bounds;
}

error_code vector_3d_get(vector_3d *v, int index, point_3d *element) {
    if(vector_3d_is_valid(*v) && index >= 0){
        if(index < v->length){
            *element = v->content[index];
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_3d_get");
            return out_of_bounds;
        }
    }
    error_code_display(uninitialized, "vector_3d_set");
    return uninitialized;
}

error_code vector_3d_resize(vector_3d *v, int size){
    if(vector_3d_is_valid(*v)){
        v->capacity = size;
        v->content = realloc(v->content, size * sizeof(point_3d ));
        return ok;
    }
    return vector_3d_default_value(v);
}

error_code vector_3d_remove(vector_3d *v, int index) {
    if(vector_3d_is_valid(*v) && index >= 0){
        if(v->length > 0){
            for (int i = index; i < v->length; i++){
                v->content[i] = v->content[i+1];
            }
            v->length--;
            return ok;
        }
        error_code_display(out_of_bounds, "vector_3d_remove");
        return out_of_bounds;
    }
    return vector_3d_default_value(v);
}

error_code vector_3d_insert(vector_3d *v, point_3d element, int index) {
    if(vector_3d_is_valid(*v) && index >= 0){
        if(index <= v->length+1){
            for (int i = v->length-1; i >= index; i--){
                if(i+1 >= v->capacity){
                    v->content[i+1] = v->content[i];
                } else {
                    vector_3d_resize(v, v->capacity + 1);
                    v->content[i+1] = v->content[i];
                }
            }
            v->content[index] = element;
            v->length++;
            return ok;
        } else {
            error_code_display(out_of_bounds, "vector_3d_insert");
            return out_of_bounds;
        }
    }
    return vector_3d_default_value(v);
}

error_code vector_3d_empty(vector_3d *v) {
    if(vector_3d_is_valid(*v)){
        point_3d p = {0,0,0};
        while(v->length > 0){
            v->content[v->length-1] = p;
            v->length--;
        }
        return ok;
    }
    return vector_3d_default_value(v);
}

error_code vector_3d_free(vector_3d *v) {
    if(vector_3d_is_valid(*v)){
        v->capacity = 0;
        v->length = 0;
        free(v->content);
        v->content = NULL;
        return ok;
    }
    return vector_3d_default_value(v);
}

point_3d vector_3d_get_last_element(vector_3d v){
    return v.content[v.length-1];
}

bool vector_3d_is_valid(vector_3d v){
    if(v.content != NULL){
        return true;
    } else {
        return false;
    }
}

error_code vector_3d_default_value(vector_3d *v){
    v->content = NULL;
    v->capacity = -1;
    v->length = -1;
    error_code_display(uninitialized, "vector_3d_default_value");
    return uninitialized;
}

bool vector_3d_is_full(vector_3d v){
    if(vector_3d_is_valid(v)){
        return v.capacity == v.length;
    } else{
        return false;
    }
}

bool vector_3d_is_empty(vector_3d v){
    if(vector_3d_is_valid(v)){
        return v.length == 0;
    } else{
        return false;
    }
}

void vector_3d_print_int(vector_3d *v) {
    printf("tab : ");
    for (int i = 0; i < v->length; i++){
        printf(" x: %f - y: %f /",v->content[i].x, v->content[i].y);
    }
    printf("\n");
}

error_code vector_3d_map(vector_3d *v, point_3d(*f)(point_3d ), vector_3d *rhs){
    if(vector_3d_is_valid(*v)){
        if(!vector_3d_is_valid(*rhs)){
            vector_3d_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            vector_3d_push(rhs, (f)(v->content[i]));
        }
        return ok;
  }
  return vector_3d_default_value(v);
}

error_code vector_3d_filter(vector_3d *v, bool(*f)(point_3d ), vector_3d *rhs){
    if(vector_3d_is_valid(*v)){
        if(!vector_3d_is_valid(*rhs)){
            vector_3d_init(rhs);
        }
        for (int i = 0; i < v->length; i++) {
            if((*f)(v->content[i])){
                vector_3d_push(rhs, v->content[i]);
            }
        }
        return ok;
  }
  return vector_3d_default_value(v);
}
