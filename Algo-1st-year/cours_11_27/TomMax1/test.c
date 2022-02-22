#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum signe{
    X,
    V,
    O
}signe;

typedef struct signe_array {
    int m;
    int n;
    signe** data;
} signe_array;

bool verif(int n, signe tab[n][n]){
    
}

int main(){
    int n = 4;

    signe_array tab;
    tab.m = n;
    tab.n = n;
    tab.data = malloc(n * sizeof(signe*));
    tab.data[0]= malloc(n * n * sizeof(signe));

// cas 1

    signe array[] = {
        X, V, X, O,
        X, O, O, O,
        O, O, X, V,
        O, V, X, X
    };
    for (int i = 0; i < n; i++) {
        tab.data[i] = tab.data[0] + i * n;
    }

    printf("fonctionne grâce à la diagonale bas-gauche vers haut-droite : \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        tab.data[i][j]= array[i * n + j];
        }
    }

    for (int i = 0; i < tab.m ; i++) {
        printf("\t");
        for (int j = 0; j < tab.n; j++) {
            printf(" %d ", tab.data[i][j]);
        }
        printf("\n");
    }
    bool resultat = verif(n, array);
    
    printf("\nresultat : ");
    printf(resultat ? "true\n" : "false\n");

// cas 2

    signe array2[] = {
        O, V, X, V,
        X, V, V, O,
        O, O, O, V,
        O, V, O, X
    };

    printf("\n\nne fonctionne pas car il n'y aucune des conditions valides : \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        tab.data[i][j]= array2[i * n + j];
        }
    }

    for (int i = 0; i < tab.m ; i++) {
        printf("\t");
        for (int j = 0; j < tab.n; j++) {
            printf(" %d ", tab.data[i][j]);
        }
        printf("\n");
    }
    bool resultat2 = verif(n, array2);
    
    printf("\nresultat 2 : ");
    printf(resultat2 ? "true\n" : "false\n");

    return 0;
}
