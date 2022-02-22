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
  assert(lst.position!=NULL);
  return (lst.position)->info;
   /*assert(!est_vide(lst) && NULL != lst.position);
   return lst.position->info;*/
}

bool est_premier(liste lst) {
  assert(lst.position!=NULL);
  return (lst.position)->prec==NULL;
   /*assert(NULL != lst.position);
   return (NULL == lst.position->prec);*/
}

bool est_dernier(liste lst) {
  assert(lst.position!=NULL);
   return (lst.position)->suiv== NULL;
}

void premier(liste* lst) {
   assert(!est_vide(*lst));
   lst->position= lst->tete;
}

bool avancer(liste* lst) {
  assert(lst->position!=NULL);
  if(!est_dernier(*lst)){
    lst->position=(lst->position)->suiv;
    return true;
  }else{
    return false;
  }
   /*if (!est_dernier(*lst)) {
      lst->position = lst->position->suiv;
      return true;
   } else {
      return false;
   }*/
}

bool reculer(liste* lst) {
   assert(lst->position!=NULL);
   if(!est_premier(*lst)){
     lst->position = (lst->position)->prec;
     return true;
   }else{
     return false;
   }

}

bool trouver(liste lst,int info) {
   /*premier(&lst);
   while (avancer(&lst)) {
      if (lst.position->info == info) {
         return true;
      }
   }
   return false;*/
}

void inserer(liste* lst,int info) {
  element * newElement= calloc(1,sizeof(element));
  newElement->info= info;
  if(lst->tete== NULL && lst->position==NULL){
    lst->tete= newElement;
    lst->position=newElement;
    newElement->suiv= NULL;
    newElement->prec=NULL;
  }else{
    if(est_dernier(*lst)){
      newElement->suiv=NULL;
      newElement->prec= lst->position;
      (lst->position)->suiv=newElement;
      lst->position=newElement;
    }else{
      newElement->suiv= lst->position->suiv;
      newElement->prec= lst->position;
      (lst->position->suiv)->prec= newElement;
      lst->position->suiv= newElement;

    }
  }




   /*element *suiv = NULL, *prec = NULL;
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
   if (est_vide(*lst)) lst->tete = lst->position;*/
}

int extraire(liste* lst) {
   assert(!est_vide(*lst) && NULL != lst->position);
   //� compl�ter
   return 0;
}

void vider(liste* lst) {
   //� compl�ter
}

void print(liste lst) {
   premier(&lst);
   while (avancer(&lst)) {
      printf("%d ",lst.position->info);
   }
}
