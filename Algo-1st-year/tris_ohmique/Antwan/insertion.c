#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


void swap(int* p_a, int* p_b){
    int tmp = *p_a;
    *p_a = *p_b;
    *p_b = tmp;
}

void insertion(int *table, int size){
    for(int i = 1; i < size; ++i){
        int value = table[i];
        int j = i;
        while(j > 0 && value < table[j-1]){
            table[j] = table[j -1];
            --j;
        }
        table[j] = value;
    }

}
int main()
{
    int table[] = {4, 7, 6, 1, 2};
    int size = 5;
    
    for (int i = 0; i < size; i++){
        printf("%d ", table[i]);
    }
    printf("\n");

    insertion(table, size);

    for (int i = 0; i < size; i++){
        printf("%d ", table[i]);
    }
    printf("\n");

    

    








}