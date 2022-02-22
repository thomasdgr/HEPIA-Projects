#ifndef BIN_TREE_H
#define BIN_TREE_H

// Structure pour un arbre binaire
typedef int cle;
typedef struct _node {
  cle key;
  struct _node* child[2];
} node;
typedef node* arbre;

// Fonctionnalités pour un arbre binaire ordonné
bool arbre_search(arbre tree,int cle);
bool arbre_insert(arbre* tree,int cle);
bool arbre_delete(arbre* tree,int cle);
void arbre_print(arbre tree,int N);
int arbre_depth(arbre tree);
int arbre_size(arbre tree);
#endif
