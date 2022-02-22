#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char** alloc_strings_array(int n, int max_len){
    char** kek = malloc(sizeof(char*) * n);
    for(int i = 0; i < n; i++){
        kek[i] = malloc(sizeof(char) * max_len);
    }
    return kek;
}

void free_strings_array(char** kek, int n){
    for(int i = 0; i < n; i++){
        free(kek[i]);
    }
    free(kek);
}

void print_strings_array(char** kek, int n){
    for(int i = 0; i < n; i++){
        printf("%s\n", kek[i]);
    }
}


void main(void){
    int n = 5;
    char **str_array = alloc_strings_array(n, 15);
    for(int i = 0; i < n; i++){
        sprintf(str_array[i], "%d", i);
    }
    print_strings_array(str_array, n);
    free_strings_array(str_array, n);
}