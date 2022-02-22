#ifndef _CHAINE_DOUBLE_H_
#define _CHAINE_DOUBLE_H_
#include <stdbool.h>

typedef struct _element {
   int info;
   struct _element* suiv;
   struct _element* prec;
} element;

typedef struct _liste {
   element* tete;
   element* position;
} liste;

liste creer();
bool est_vide(liste lst);
int valeur(liste lst);
bool est_premier(liste lst);
bool est_dernier(liste lst);
void premier(liste* lst);
bool avancer(liste* lst);
bool reculer(liste* lst);
bool trouver(liste lst,int info);
void inserer(liste* lst,int info);
int extraire(liste* lst);
void vider(liste* lst);
void print(liste lst);

#endif


