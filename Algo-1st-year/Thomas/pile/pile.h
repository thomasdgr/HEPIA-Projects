#ifndef PILE_H
#define PILE_H
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct _pile{
  int *tab;
  int sommet;
  int capacite;
} pile;

pile pile_create(int taille);
int pile_destroy(pile *stack);
bool pile_est_vide(pile stack);
bool pile_est_pleine(pile stack);

int pile_empiler(pile *stack, int nombre);
int pile_depiler(pile *stack, int nombre);
int pile_step(pile *stackGauche, pile *stackDroite, int nombre);
//Comparaison indique la comparaison à effectuer:
//0:Transfert nombre de la pile de Gauche vers pile de Droite
//1:Transfert nombre de la pile de Droite vers pile de Gauche
int pile_transfert(pile *stackGauche, pile *stackDroite, int nombre, int cas);
int pile_transvasement(pile *stackGauche, pile *stackDroite);
int pile_tri_complet(pile *stackGauche, pile *stackDroite,int *tableau, int tailleTableau);
void pile_print(pile stack);

#endif
