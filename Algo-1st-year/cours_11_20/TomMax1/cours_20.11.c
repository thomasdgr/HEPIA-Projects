#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct _element {
   int n;
   struct _element* suivant;
} element;
typedef element* liste;

liste liste_creer() {
   return NULL;
}

bool liste_est_vide(liste lst) {
   return NULL == lst;
}

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

liste liste_extraire(liste lst,int val) {
   element* prec = lst;
   element* crt = lst;
   while ( crt != NULL) {
        if (crt->n == val) {
            if (crt == prec) {
                 prec = crt->suivant;
            } else {
                prec->suivant = prec->suivant;
            }
            prec = crt;
            crt = crt->suivant;
        } 
    }
    free(crt);
    free(prec);
    return lst;
}

element* liste_recherche(liste lst,int val) {
    // MARCHE PAS POUR L INSTANT
   if(lst != NULL){
        for (int i = 0; i < sizeof(lst); i++){
            if (lst->n == val){
                return lst->n;
            } 
        }
       return NULL;
   }   
   return NULL;
}

void print(liste lst) {
   element *crt = lst;
   	while ( crt != NULL) {
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

