#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "chaine_double.h"

liste creer() {
   liste lst;
   lst.tete = NULL;
   lst.position = NULL;
   return lst;
}

bool est_vide(liste lst) {
   return (NULL == lst.tete);
}

int valeur(liste lst) {
   assert(!est_vide(lst) && NULL != lst.position);
   return lst.position->info;
}

bool est_premier(liste lst) {
   assert(NULL != lst.position);
   return (lst.position->prec==NULL);
}

bool est_dernier(liste lst) {
   assert(NULL != lst.position);
   return (lst.position->suiv==NULL);
}

void premier(liste* lst)
{
   lst->position = lst->tete;
}

bool avancer(liste* lst) {
   if (!est_dernier(*lst)) {
      lst->position = lst->position->suiv;
      return true;
   } else {
      return false;
   }
}

bool reculer(liste* lst) {
   if (!est_premier(*lst))
   {
     lst->position = lst->position->prec;
     return true;
   }
   else
   {
     return false;
  }
}

bool trouver(liste lst,int info) {
   premier(&lst);
   while (avancer(&lst)) {
      if (lst.position->info == info) {
         return true;
      }
   }
   return false;
}

void inserer(liste* lst,int info) {
   element *suiv = NULL, *prec = NULL;
   if (!est_vide(*lst)) {          // Insertion apr�s / avant
      suiv = lst->position->suiv;  // suiv = lst->position;
      prec = lst->position;        // prec = lst->position->prec;
   }
   lst->position = (element*)malloc(sizeof(element));
   lst->position->info = info;
   lst->position->suiv = suiv;
   lst->position->prec = prec;
   if (NULL != suiv) suiv->prec = lst->position;
   if (NULL != prec) prec->suiv = lst->position;
   if (est_vide(*lst)) lst->tete = lst->position;
}

int extraire(liste* lst) {
   assert(!est_vide(*lst));
   element *temp = lst->position;
   if(temp->prec == NULL)
   {
     lst->tete = temp->suiv;
     lst->position = temp->suiv;
     if (lst->position != NULL && lst->tete !=NULL)
     {
       lst->position->prec = temp->prec;
       temp->suiv = NULL;
     }
   }
   else
   {
     reculer(lst);
     lst->position->suiv = temp->suiv;
     if(temp->suiv == NULL)
     {
       temp->prec = NULL;
     }
     else
     {
       temp->suiv->prec = lst->position;
     }
   }
   int info_extrait = temp->info;
   free(temp);
   return info_extrait;
}

void vider(liste* lst)
{
   assert(!est_vide(*lst) && NULL != lst->position);
   while(!est_vide(*lst))
   {
     extraire(lst);
   }
}

void print(liste lst) {
   premier(&lst);
   do
   {
      printf("%d ",lst.position->info);
   }while (avancer(&lst));
}
