#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hachage.h"

// Hachage de la clé (chaine de caractère <nom>)
// Retourne un indice entre 0 et <length>-1 compris
int hash_nom(int length,char *nom) {
   int h = 0;
   for (int i = 0; nom[i] != '\0'; i++)
   {
     h += nom[i] * i;
   }
   return h % length;
}

// Autre hachage de la clé (chaine de caractère <nom>)
// Retourne un indice entre 1 et <length>-1 compris
int hash_nom2(int length,char *nom) {
   int h = 0;
   // à compléter
   return h+1;
}

// Allocation et initialisation d'un annuaire
annuaire annuaire_init(int length) {
   annuaire annuaire = {length,0,NULL};
   if (length > 0) {
      annuaire.table = calloc(length,sizeof(entree));
   }
   return annuaire;
}

// Remise à zéro et désallocation d'un annuaire
void annuaire_free(annuaire* annu)
{
   free(annu->table);
   annu->table = NULL;
   annu->length = 0;
   annu->nb = 0;
}

// Calcul de l'indice où insérer, sinon où se trouve l'information
static int indice(annuaire annu,char* nom,bool inserting) {
   int cnt = 0;
   int h = hash_nom(annu.length,nom);
   //int saut = 1 (séq.) ou k (lin.) ou -1 (quadrat.)
   int saut = hash_nom2(annu.length,nom);  // double hachage
   // srand(hash_nom2(annu.length,nom))  (pseudo-aléa)
   while (cnt < annu.length) {
      switch(annu.table[h].state) {
      case TAKEN:
         if (strcmp(nom,annu.table[h].person.nom) == 0) {
            return h;
         }
         break;
      case DELETED:
         if (inserting) {
            return h;
         }
         break;
      case EMPTY: return h;
      }
      //saut += 2 (quadrat.) ou saut = rand() (pseudo-aléa)
      h = (h+saut)%annu.length;
      cnt++;
   }
   return -1;
}

// Recherche si une clé est déjà dans l'annuaire
bool annuaire_search(annuaire annu,char* nom)
{
   int h = indice(annu,nom,false);
   return (h >= 0 && annu.table[h].state == TAKEN);
}

// Insertion d'une information avec sa clé dans l'annuaire
bool annuaire_insert(annuaire* annu,personne person)
{
   if (!annuaire_search(*annu,person.nom)) {
      int h = indice(*annu,person.nom,true);
      annu->table[h].state = TAKEN;
      annu->table[h].person = person;
      annu->nb++;
      return true;
   }
   return false;
}
void affichage(annuaire annu)
{
  for (int i = 0; i < annu.length; i++)
  {
    printf("%s\n", annu.table[i].person.nom);
  }
}
// Suppression d'une information avec sa clé dans l'annuaire
bool annuaire_remove(annuaire* annu,char* nom)
{
   if (annuaire_search(*annu,nom))
   {
     int h = indice(*annu,nom,false);
     annu->table[h].state = DELETED;
     annu->nb--;
     return true;
   }
   return false;
}
