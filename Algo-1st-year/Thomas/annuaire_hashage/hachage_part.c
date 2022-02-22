#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "hachage.h"

// Hachage de la clé (chaine de caractère <nom>)
// Retourne un indice entre 0 et <length>-1 compris

void annuaire_print(annuaire annu){
  printf("annuaire de taille: %d\n", annu.nb);
  printf("------------\n");
  for(int i=0; i<annu.length;i++){
    printf("entrée %d: %s state:%d\n",i, annu.table[i].person.nom,annu.table[i].state);
  }
  printf("------------\n");
}
int hash_nom(int length,char *nom) {
   int h = 0;
   h= nom[0]%length;
   return h;
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
void annuaire_free(annuaire* annu) {
   free(annu->table);
   annu->table = NULL;
   annu->length = 0;
   annu->nb = 0;
}

// Calcul de l'indice où insérer, sinon où se trouve l'information
static int indice(annuaire annu,char* nom,bool inserting) {
  int compteur=0;
  int indice= hash_nom(annu.length,nom);
  while(compteur<annu.length){
    //printf("case %d",annu.table[indice].state);
    switch(annu.table[indice].state){
      case 0:
        printf("case empty\n");
        return indice;
        break;
      case 1:
        if(strcmp(nom,annu.table[indice].person.nom)==0){
          printf("case taken\n");
          return indice;
        }
        break;
      case 2:
        printf("case deleted\n");
        if(inserting){
          return indice;
        }
        break;

    }

    indice=(indice +1) %annu.length;
    compteur++;
  }
  return -1;

}

// Recherche si une clé est déjà dans l'annuaire
bool annuaire_search(annuaire annu,char* nom) {
  int indice= hash_nom(annu.length, nom);
  if(indice>=0 && strcmp(nom,annu.table[indice].person.nom)!=0){
    //printf("no pb index:%d\n",indice);
    return 0;
  }else{
    return 1;
  }
}

// Insertion d'une information avec sa clé dans l'annuaire
bool annuaire_insert(annuaire* annu,personne person) {
  int i= indice(*annu, person.nom,true);
  if(i>=0 && !annuaire_search(*annu,person.nom)){
    printf("indice final:%d\n",i);
    annu->nb+=1;
    annu->table[i].person=person;
    annu->table[i].state=1;
    return 1;
  }else{
    return -1;
  }


}

// Suppression d'une information avec sa clé dans l'annuaire
bool annuaire_remove(annuaire* annu,char* nom) {
   int i= indice(*annu, nom, false);
   if(i>=0 && !strcmp(nom,annu->table[i].person.nom))
   {
     annu->table[i].state=2;
     annu->nb-=1;
     return true;
   }else{
     return false;
   }

}
