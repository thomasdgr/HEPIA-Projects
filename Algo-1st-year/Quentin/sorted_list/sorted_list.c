#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct _element {
   int n;
   struct _element* suivant;
} element;
typedef element* liste;

// Crée une liste vide
liste liste_creer() {
   return NULL;
}

// Teste si la liste vide
bool liste_est_vide(liste lst) {
   return NULL == lst;
}

// Retourne un pointeur sur l'élement avant l'emplacement d'insertion;
// ce pointeur est nul si la liste est vide ou si l'insertion est en tête de liste
element* position(liste lst,int val) {
   element* pos = lst;
   if (liste_est_vide(lst) || val <= lst->n) {
      pos = NULL;
   } else {
      while (NULL != pos->suivant && val > pos->suivant->n) {
         pos = pos->suivant;
      }
   }
   return pos;
}

// Insère un élément dans la liste triée et retourne la liste mise à jour
liste liste_inserer(liste lst,int val) {
   element* tmp = malloc(sizeof(element));
   tmp->n = val;
   element* pos = position(lst,val);
   if (NULL == pos) { // insertion dans une liste vide ou en tête de liste
      tmp->suivant=NULL;
      lst=tmp;
   } else {           // insertion au milieu ou en fin de liste
      element* pos= position(lst,val);
      tmp->suivant= pos->suivant;
      pos->suivant= tmp;
   }
   return lst;
}

// Extrait un élément avec la valeur <val> et retourne la liste mise à jour;
// la liste est inchangée si elle est initialement vide
// ou si la valeur est absente
liste liste_extraire(liste lst,int val) {
   //element* prec = lst;
   element* pos = position(lst,val);

   if (NULL != pos && val == pos->suivant->n) {
     int valeur=pos->suivant->n;
     element* delete= pos->suivant;
     pos->suivant=pos->suivant->suivant;
    free(delete);
    return lst;
   }else{
     element* delete=lst;
     lst= lst->suivant;
     free(delete);
     return lst;
   }

}

// Retourne un pointeur sur l'élément qui contient <val> ou un pointeur nul
// si la liste est vide ou la valeur absente
element* liste_recherche(liste lst,int val) {
   // à compléter
   return NULL;
}

// Imprime le contenu de la liste
void print(liste lst) {
  element * affiche = lst;
   while(affiche!=NULL){
     printf("%d ",affiche->n);
     affiche= affiche->suivant;
   }
   printf("\n");
}

int main(int argc, char** argv) {
   liste lst = liste_creer();
   char str[20];
   do {
      printf("Insert: ");
      scanf("%s", str);
      if (0 == strcmp("quit",str)) break;
      lst = liste_inserer(lst,atoi(str));
      print(lst);
      //printf("\n");
   } while (true);
   do {
      printf("Extract: ");
      scanf("%s", str);
      if (0 == strcmp("quit",str)) break;
      lst = liste_extraire(lst,atoi(str));
      print(lst);
      printf("\n");
   }  while (true);
   //affiche(lst);
   return 0;
}
