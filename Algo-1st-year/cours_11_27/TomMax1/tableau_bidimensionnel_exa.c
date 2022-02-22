#include <stdio.h>
#include <stdlib.h>

void main() {
    int size = 5;
    double tab[size][size];


    double alea = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(i-1 >= 0 && tab[i][j] < tab[i-1][j]){
                tab[i][j] = tab[i-1][j];
            }
            if(i+1 < size && tab[i][j] < tab[i+1][j]){
                tab[i][j] = tab[i+1][j];
            }
            if(j-1 >= 0 && tab[i][j] < tab[i][j-1]){
                tab[i][j] = tab[i][j-1];
            }
            if(j+1 < size && tab[i][j] < tab[i][j+1]){
                tab[i][j] = tab[i][j+1];
            }
        }
    }      
}