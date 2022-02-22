#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"

static void swap(int* a,int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapsort(int* tab,int size) {
   entassement(tab,size);
   swap(tab,tab+size-1);
   for (int s=size-1;s>1;s--) {
      promotion(tab,s,0);
      swap(tab,tab+s-1);
   }
}
void entassement(int* tab,int size)
{
    for (int i = (size/2) - 1; i > -1; i--)
    {
      promotion(tab, size, i);
    }
}

void promotion(int* tab,int size,int i) {

   int ind_max = max3(tab,size,i);
   if (ind_max != i) {
      promotion(tab,size,i);
   }
}

int max3(int* tab,int size,int i) {
   int ind_max = i;
   int left = fils_g(i), right = fils_d(i);
   if (tab[left] > tab[ind_max] && tab[left] > tab[right]) {
      ind_max = left;
   }
   else if (tab[right] > tab[left] && tab[right] > tab[ind_max]) {
     ind_max = right;
   }
   if (ind_max != i) {
     swap(&tab[i], &tab[ind_max]);
   }
   return ind_max;
}

int fils_g(int i) {
   return (2*i)+1;
}
void print(int* tab,int size,char* str) {
   for (int i=0;i<size;i++) {
      printf("%d ",tab[i]);
   }
   printf("%s",str);
}

int fils_d(int i) {
   return (2*i)+2;
}
