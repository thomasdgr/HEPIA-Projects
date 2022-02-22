#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../gini/gini.h"

// retourne le minimum entre 2 objets
#define MIN(a,b) (((a)<(b))?(a):(b))

// structure représentant un noeud de l'arbre
typedef struct elem{
  double coupe;
  int index_coupe;
  struct elem * tab[2]; // enfant gauche et enfant droit
  int classe;
} elem;

// pointeur sur le premier élément de l'arbre
typedef elem * arbre;

// création d'un élément de l'arbre
elem * create_elem(double coupe, int index_cut);

// construction récursive de l'arbre
void build_tree(arrayNode kek, elem * node, int profondeur_max, int profondeur, double pourcentage_min, int id_node, int minimal_size);

// suppression de l'arbre
void free_tree(arbre tree);

// test du modèle avec un set donné et un arbre existant
double train(arrayNode content, elem* tree);

// retourne la classe d'un noeud trouvée à partir de l'arbre
int get_class(node n, elem*tree);

// affichage de l'arbre (code repris de Ray Hulha sur stackoverflow et modifié pour ce cas de figure)
int _print_t(elem *tree, int is_left, int offset, int depth, char s[255][255]);
void print_t(elem *tree, int depth);

#endif