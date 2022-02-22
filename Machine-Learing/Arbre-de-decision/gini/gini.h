#ifndef GINI_H
#define GINI_H

#include "../arrayNode/arrayNode.h"

// retourne l'indice de gini, la coupe et la matrice pour un attribut selon une liste de noeuds variables (modifiée à cause de la coupe) 
double gini(single * data, int id, int nb_elem, double * coupe, int array[2][2]);

// retourne le nombre de valeurs possibles pour un attribut donné
int getSizeFromId(int id);

// retourne la meilleure coupe, la matrice et gini parmis tous les attributs possibles et toutes leurs valeurs possibles
int best_cut(int size, arrayNode kek, double* best_gini, double* coupe, int array[2][2]);

#endif