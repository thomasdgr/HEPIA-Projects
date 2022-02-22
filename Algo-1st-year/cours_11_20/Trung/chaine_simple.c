#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "string.h"

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
      tmp->suivant = lst;
      lst = tmp;
   } else {           // insertion au milieu ou en fin de liste
      tmp->suivant = pos->suivant;
      pos->suivant = tmp;
   }
   return lst;
}

// Extrait un élément avec la valeur <val> et retourne la liste mise à jour;
// la liste est inchangée si elle est initialement vide
// ou si la valeur est absente
liste liste_extraire(liste lst,int val) {
   element* prec = lst;
   element* crt = lst;
   // boucle pour placer <val>: prec->n < val <= crt->n
   while (crt != NULL && val >= crt->n)
   {
     // liste non-vide et <val> présente de la liste
     if (NULL != crt && val == crt->n) {
        if (crt == prec) { // extraction en début de liste
           lst = lst->suivant;
        } else { // extraction en milieu ou fin de liste
           prec->suivant = crt->suivant;
        }
        free(crt);
        return lst;
     }
     prec = crt;
     crt = crt->suivant;
   }
   return lst;
}

// Retourne un pointeur sur l'élément qui contient <val> ou un pointeur nul
// si la liste est vide ou la valeur absente
element* liste_recherche(liste lst,int val)
{
   element *pos = position(lst,val);
   if (liste_est_vide(lst))
   {
     return NULL;
   }
   else if(NULL == pos && val == lst->n)
   {
     return lst;
   }
   else if(NULL != pos->suivant && val == pos->suivant->n)
   {
     return pos->suivant;
   }
   else
   {
     return NULL;
   }
}

// Imprime le contenu de la liste
void print(liste lst)
{
  element* crt = lst;
  while (crt != NULL)
  {
    printf("%d ", crt->n);
    crt = crt->suivant;
  }
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
      printf("\n");
   } while (true);
   do {
      printf("Extract: ");
      scanf("%s", str);
      if (0 == strcmp("quit",str)) break;
      lst = liste_extraire(lst,atoi(str));
      print(lst);
      printf("\n");
   }  while (true);
   return 0;
}
