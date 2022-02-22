#include "quadtree.h"
int main(){
  srand(time(NULL));
  node * tree = tree_create(3);
  printf("-----\n");
  print_int_tree(tree,0);
  printf("-----\n");
  tree_sum(tree);
  printf("-----\n");
  print_int_tree(tree,0);
  printf("-----\n");
  printf("La profondeur de l'arbre est de %d\n", tree_depth(tree));
  printf("value i:3 j:3 : %d\n",position(tree,7,7,3)->info);
  desalloc_tree(tree);
  free(tree);

  return 0;
}
