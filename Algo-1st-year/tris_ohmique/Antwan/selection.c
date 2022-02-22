#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


void swap(int* p_a, int* p_b){
    int tmp = *p_a;
    *p_a = *p_b;
    *p_b = tmp;
}

void selection_step(int* table, int size, int i){
    for (int j = i; j + 1 < size ; j++){
        if(table[i] > table[j + 1])
            swap(table + i, table + j +1);
    }
}

void selection(int* table, int size){
    for (int i = 0; i < size; i++){
        selection_step(table, size, i);
    }
}


int main(){
    int table[] = {4, 7, 6, 1, 2};
    int size = 5;
    
    for (int i = 0; i < size; i++){
        printf("%d ", table[i]);
    }
    printf("\n");

    selection(table, size);

    for (int i = 0; i < size; i++){
        printf("%d ", table[i]);
    }
    printf("\n");
}