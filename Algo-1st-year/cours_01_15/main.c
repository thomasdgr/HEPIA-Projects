#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heapsort.h"

void print(int* tab,int size,char* str);

int main(int argc, char** argv) {
   srand(time(0));
   int size = 11;
   //int* tab = malloc(size*sizeof(int));
   int tab[11] = {1,5,8,2,3,0,4,12,13,8,6};

   print(&tab,size,"\n=========\n");
   heapsort(&tab,size);
   print(&tab,size,"\n=========\n");
   return 1;
}
