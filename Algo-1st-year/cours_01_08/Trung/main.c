#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "bin_tree.h"

void main() {
   bool b;
   int val;
   arbre tree = NULL;
   printf("Hello world\n");
   arbre_print(tree,1);
   do {
      printf("insert val = ");
      scanf("%d",&val);
      b = arbre_insert(&tree,val);
      arbre_print(tree,1);
   } while (b);
   node* nd;
   do {
      printf("delete val = ");
      scanf("%d",&val);
      b = arbre_delete(&tree,val);
      arbre_print(tree,1);
   } while (NULL != tree);
}
