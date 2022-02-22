#include <stdio.h>
#include <stdlib.h>

void main() {
    int size = 5;
    double output_tab[size];
    double pile[size];
    double tab[5] = {1.2, 3.2, -1.1, 7.2, 2.5};
    int count = 0;
    int count1 = 0;
    int count2 = 0;

    double alea = 0;

    for (int i = 0; i < size; i++) {
        alea = rand() / ((double) RAND_MAX);
        if (alea < 0.5){
            pile[count1] = insert(tab[i], size, output_tab);
            count1++;
        } else {
            output_tab[count2] = insert (tab[i], size, output_tab);
            count2++;
        }
    }
    int pile_size = sizeof(pile);
    int output_tab_size = sizeof(tab);
    for (int j = output_tab_size; j < pile_size + output_tab_size; j++){
        output_tab[j+1] = pile[count];
        count++;
    }
    
    
}

int insert(int n, int size_array, double output_tab[]){
    for (int i = 0; i < size_array; i++){
        if(i+1 == sizeof(output_tab)){
            output_tab[i+1] = n;
        }
    }
    return output_tab;
}