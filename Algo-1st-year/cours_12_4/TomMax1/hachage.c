#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef enum _etat {vide, occupé, supprmié} etat;

typedef struct _personne {
   char nom[100]; 
   int tel;
} personne;

typedef struct entree {
   etat state;
   personne person;
} entree;

typedef struct annuaire {
   int length;
   int nb_elem_vide;
   entree* table;
} annuaire;

int hash(int length,char* nom);
annuaire build(int length);
void free(annuaire* annu);
int indice(annuaire annu,char* nom,bool inserting);
bool search(annuaire annu,char* nom);
bool insert(annuaire* annu,personne person);
bool remove(annuaire* annu, char *nom);

int hash(int length, char *nom) {
   int h = 0;
   for(int i = 0; nom[i] != '\0'; i++){
       h+= nom[i] * i;
   }
   return h % length;
}

annuaire build(int length) {
    assert(length > 0);
    annuaire annu = {length,0,NULL};
    annu.table = calloc(length,sizeof(entree));
    return annu;
}

void free(annuaire* annu) {
   free(annu->table);
   annu->nb_elem_vide = -1;
   annu->length = 0;
   annu->table = NULL;
}

int indice(annuaire annu, char* nom, bool to_insert) {
   int cnt = 0;
   int ind = hash_nom(annu.length,nom);
   while (cnt < annu.length) {
      switch(annu.table[ind].state) {
      case supprmié:
         if (to_insert) {
            return ind; 
         } else {
            break;
         }
      case vide: return ind;
      case occupé:
         if (strcmp(annu.table[ind].person.nom, nom) == 0) {
            return ind;
         } else {
            break;
         }
      }
      ind = (ind + 1)%annu.length;
      cnt++;
   }
   return -1;
}

bool search(annuaire annu,char* nom) {
   int ind = indice(annu, nom, false);
   return (ind >= 0 && strcmp(annu.table[ind].person.nom, nom) == 0);
}

bool insert(annuaire* annu, personne person) {
   if (!search(*annu, person.nom)) {
      int ind = indice(*annu, person.nom, true);
      annu->table[ind].state = occupé;
      annu->table[ind].person = person;
      annu->nb_elem_vide++;
      return true;
   }
   return false;
}

bool remove(annuaire* annu,char* nom) {
   if (!search(*annu, nom)) {
      int ind = indice(*annu, nom, false);
      annu->table[ind].state = supprmié;
      //annu->table[h].person = person;
      annu->nb_elem_vide--;
      return true;
   }
   return false;
}

