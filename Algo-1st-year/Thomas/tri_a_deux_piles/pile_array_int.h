#ifndef PILE_ARRAY_INT_H
#define PILE_ARRAY_INT_H

#include <stdbool.h>

typedef struct _pile {
   int* data;
   int sommet;
   int capacite;
} pile;

//Créer une nouvelle pile vide
pile pile_creer(int max);
//Libérer le tableau, mettre la capacité à < -1
void pile_detruire(pile* stack);
//Empiler un élement au sommet de pile
void pile_empiler(pile* stack,int data);
//Dépiler un élément du sommet de la pile
int pile_depiler(pile* stack);
//Tester si la pile est valide
bool pile_est_valide(pile stack);
//Tester si la pile est vide
bool pile_est_vide(pile stack);
//Tester si la pile est pleine
bool pile_est_pleine(pile stack);
//Consulter l'élément au sommet de la pile
int pile_sommet(pile stack);
//Compter du nombre d'éléments de la pile:
int pile_count(pile stack);

#endif
