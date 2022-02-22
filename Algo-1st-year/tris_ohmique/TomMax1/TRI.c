#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

void main () {

    int size_array = 0;
    printf("Saisir la taille du tableu à réaliser : ");
    scanf("%d", &size_array);
    printf("\n");

    int array[size_array];
    for(int i = 0; i < size_array; i++){
        printf("Saisir l'élément %d à mettre dans le tableau : ", i+1);
        scanf("%d", &array[i]);
    }

    tri_par_insertion(size_array, array);

    tri_par_selection(size_array, array);

    tri_a_bulle(size_array, array);

    //quicksort(size_array, array, 0, sizeof(array)-1);

    // conclusion le tri à bulle c'est 100 fois mieux que les autres

 }

int swap(int n, int array[n]){
    if (n <= 0){
        return 0;
    }   
    int tmp = array[n];
    array[n] = array[n+1];
    array[n+1] = tmp;
    return 1;
}

int tri_par_insertion(int n, int array[n]){ // j'ai juste combiné les deux fonctions du cours en une seule
    if (n <= 0){
         return 0;
    }
    int index = 0;
    int position = 0; 
    for (int i = 1; i < n; i++) {
        index = array[i]; // je prends un élément élément
        position = i-1; // je trouve sa position 
        while (position >= 0 && array[position] > index) { // tant qu'on est pas revenu au début du tableau et que index est pas à la bonne place 
            array[position+1] = array[position]; // on change les positions jusq'a trouver une position ou le nombre est plus grand que index pour les inverser
            position--; // on diminue la position pour se concentrer sur les éléments suivant (du coup vers la gauche dans le tableau)
        } 
        array[position+1] = index; // on place index à la bonne position
    }
    printf("\nTableau trié par insertion :\n");
    for (int i = 0; i < n; i++)
        printf("%d - ", array[i]);
    printf("\n"); 
    return 1;
}

int tri_a_bulle(int n, int array[n]){ // application de la fonction vue en cours
    if (n <= 0){
         return 0;
    }
    int tmp = 0;
    for (int i = 0; i < n; i++) {
        if (array[i+1] < array[i]){  // suffit de permuter les éléments du tableau si le suivant est plus grand que le précédant
            swap(n,array[i]);
        }
    }
    printf("\nTableau avec le tri à bulle :\n");
    for (int i = 0; i < n; i++)
        printf("%d - ", array[i]);
    printf("\n"); 
    return 1;
}


int tri_par_selection(int n, int array[n]){
    if (n <= 0){
         return 0;
    }
    int index = 0;
    int tmp = 0;
    for (int i = 0; i < (n - 1); i++) { // je parcours chaque element du tableau
        index = i; 
        for (int j = i+1; j < n; j++) { // je regarde si l'élément j est superieur à l'élément i
            if (array[index] > array[j])
            index = j;
        }
        if (index != i) { // si c'est le cas j'échange les index
            swap(n,array[i]);
        }
        // autrement j'essaye avec l'élément suivant
    }
    printf("\nTableau trié par séléction :\n");
    for (int i = 0; i < n; i++){
        printf("%d - ", array[i]);
    }
    printf("\n");
    return 1;
}

/*int partition(int n,int array[n],int first,int last) {
    if (n <= 0){
        return 0;
    }
    int pivot = array[last];
    int i = first-1;
    int j = last;
    int tmp1 = 0;
    int tmp2 = 0;
    while (true) {
        do{
            i++;
        } while(array[i]<pivot);
        do{
            j--;
        } while(array[j]>=pivot);
        if (i >= j) {
            break;
        }
        tmp1 = array[i];
        array[i] = array[j];
        array[j] = tmp1;
    }
    tmp2 = array[i];
    array[i] = array[last];
    array[last] = tmp2;
    return i;
}

int quicksort(int n,int array[n],int first,int last) {
    if (n <= 0){
        return 0;
    }
    if (first < last) {
        int millieu = partition(n,array,first,last);
        if (first < millieu-1) {
            quicksort(n,array,first,millieu-1);
        }
        if (millieu+1 < last) {
            quicksort(n,array,millieu+1,last);
        }
    }
    printf("\nTableau avec le tri à bulle :\n");
    for (int i = 0; i < n; i++)
        printf("%d - ", array[i]);
    printf("\n");
    return 1;
}*/