#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void print(int size,int tab[size]) {
  printf("-------------\n");
   for (int i=0;i<size;i++) {
      printf("%d ",tab[i]);
   }
   printf("\n");
   printf("-------------\n");
}

void random_tab(int size,int tab[size],int inf,int sup) {
   assert(sup > inf);
   for (int i=0;i<size;i++) {
      tab[i] = inf+rand()%(sup-inf);
   }
}

void swap(int* p_a,int* p_b) {
   int tmp = *p_a;
   *p_a = *p_b;
   *p_b = tmp;
}

// Partition du tableau <array> autour d'une valeur pivot:
// compléter le code
int partition(int size,int array[size],int first,int last) {
   int pivot = array[last];
   int i = first,j = last;
   int valeurTemporaire=0;
   while (true) {
      // à compléter pour <i>: do {...} while (...);
      while(array[i]<=pivot && i<j){
        i++;

      }

      while(array[j]>=pivot && j>i){
        j--;
          //printf("Boucle j\n");

      }
      // à compléter pour <j>: do {...} while (...);
      if (i >= j) {
         break;
      }
      valeurTemporaire=array[i];
      array[i]=array[j];
      array[j]=valeurTemporaire;
      //print(size,array);
      //printf(" i:%d j:%d\n",i,j);
      //printf("\n");

      // à compléter: échanger cases <i> et <j> du tableau <array>


   }
   // à compléter: échanger cases <i> et <last> du tableau <array>
   valeurTemporaire=array[i];
   array[i]=array[last];
   array[last]=valeurTemporaire;
   return i;
}

// Tri rapide récursif
void quicksort(int size,int array[size],int first,int last) {
   if (first < last) {
      int midpoint = partition(size,array,first,last);
      if (first < midpoint-1) {
         quicksort(size,array,first,midpoint-1);
      }
      if (midpoint+1 < last) {
        printf("recurs\n");
         quicksort(size,array,midpoint+1,last);
         print(size,array);
         printf("\n");
      }
   }
}
void quicksort_gauche(int size,int array[size],int first,int last) {
   if (first < last) {
      int midpoint = partition(size,array,first,last);
      if (first < midpoint-1) {
         quicksort_gauche(size,array,first,midpoint-1);
      }
   }
}
void quicksort_droit(int size,int array[size],int first,int last) {
   if (first < last) {
      int midpoint = partition(size,array,first,last);
       if (midpoint+1 < last) {
        //printf("recurs\n");
         quicksort_droit(size,array,midpoint+1,last);
         //print(size,array);
         //printf("\n");
      }
   }
}
// Test si le tableau <array> est ordonné croissant
void test_ordre(int size,int array[size]) {
   for (int i=0;i<size-1;i++) {
      if (array[i] > array[i+1]) {
         printf("erreur");
         return;
      }
   }
   printf("ok");
}

int main(int argc,char** argv) {
   int size = atoi(argv[1]);
   int seed = atoi(argv[2]);
   srand(seed);
   int* res = (int*)malloc(size*sizeof(int));
   for (int k=0;k<1;k++) {
      random_tab(size,res,0,100);
      print(size,res);
      //quicksort_gauche(size,res,0,size-1);
      //print(size,res);
      //quicksort_droit(size,res,0,size-1);
      quicksort(size,res,0,size-1);
      print(size,res);

      test_ordre(size,res);
   }
}
