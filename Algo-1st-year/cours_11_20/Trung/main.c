#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "chaine_double.h"

int main(int argc,char** argv)
{
   liste lst = creer();
   int info;
   inserer(&lst,3);
   premier(&lst);
   print(lst);
   printf("\n");
   inserer(&lst,5);
   premier(&lst);
   print(lst);
   printf("\n");
   inserer(&lst,8);
   premier(&lst);
   print(lst);
   printf("\n");
   inserer(&lst,2);
   premier(&lst);
   print(lst);
   printf("\n");
   inserer(&lst,7);
   premier(&lst);
   print(lst);
   printf("\n");
   inserer(&lst,11);
   premier(&lst);
   print(lst);
   printf("\n");
   info = extraire(&lst);
   print(lst);
   printf("\n");
   avancer(&lst);
   avancer(&lst);
   info = extraire(&lst);
   print(lst);
   printf("\n");
   info = extraire(&lst);
   print(lst);
   printf("\n");
   info = extraire(&lst);
   print(lst);
   printf("\n");
   vider(&lst);
   return 0;
}
