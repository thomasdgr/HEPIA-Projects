#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


void swap(int* p_a, int* p_b){
    int tmp = *p_a;
    *p_a = *p_b;
    *p_b = tmp;
}


void bulles_step(int* table, int size){
    for (int i = 0; i <size -1; i++){
        if(table[i] > table[i+1]){
            swap(table +i , table+i+1);
        }
    }
}
void bulles(int* table, int size){
    for (int i = size; i >=2; i--){
        bulles_step(table, i);
    }
}



int main(){
    int table[] = {4, 7, 6, 1, 2};
    int size = 5;
    
    for (int i = 0; i < size; i++){
        printf("%d ", table[i]);
    }
    printf("\n");

    bulles(table, size);

    for (int i = 0; i < size; i++){
        printf("%d ", table[i]);
    }
    printf("\n");
}