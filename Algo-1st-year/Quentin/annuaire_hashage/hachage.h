#ifndef HACHAGE_H
#define HACHAGE_H
#include <stdbool.h>

#define STR_SIZE 80

// Information avec sa clé
typedef struct _personne {
   char nom[STR_SIZE]; // clé
   int tel; // info
} personne;

// Statut d'une entrée de la table
typedef enum _etat {EMPTY,TAKEN,DELETED} etat;

// Information et son statut
typedef struct _entree {
   etat state;
   personne person;
} entree;

// Table de hachage
typedef struct _annuaire {
   int length;
   int nb;
   entree* table;
} annuaire;

// Hachage de la clé (chaine de caractère <nom>)
// Retourne un indice entre 0 et <length>-1 compris
int hash_nom(int length,char* nom);
// Autre hachage de la clé (chaine de caractère <nom>)
// Retourne un indice entre 1 et <length>-1 compris
int hash_nom2(int length,char* nom);
// Allocation et initialisation d'un annuaire
annuaire annuaire_init(int length);
// Remise à zéro et désallocation d'un annuaire
void annuaire_free(annuaire* annu);
// Calcul de l'indice où insérer, sinon où se trouve l'information
bool annuaire_search(annuaire annu,char* nom);
// Insertion d'une information avec sa clé dans l'annuaire
bool annuaire_insert(annuaire* annu,personne person);
// Suppression d'une information avec sa clé dans l'annuaire
bool annuaire_remove(annuaire* annu, char *nom);

void annuaire_print(annuaire annu);
#endif
