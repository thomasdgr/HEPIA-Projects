#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

const int INCR = 100;
typedef struct _queue {
   int* data;
   int debut; //tete à l'index 0
   int capacite;
} queue;

bool queue_est_valide(queue fa) {
   return (fa.capacite > 0 && fa.debut >= -1);
}

bool queue_est_vide(queue fa) {
   assert(queue_est_valide(fa));
   return (-1 == fa.debut);
}

bool queue_est_pleine(queue fa) {
   if(queue_est_valide(fa)){
        return fa.debut == fa.capacite-1;
    }
}

int queue_count(queue fa) {
   int cnt = 0;
   /*while (fa.debut != NULL){
       fa = fa.capacite;
       cnt++;
   }*/   
   return cnt;
}

int queue_tete(queue fa) {
   assert(!queue_est_vide(fa));
   return fa.data[0]; 
}

int queue_debut(queue fa) {
   assert(!queue_est_vide(fa));
   return fa.data[fa.debut]; 
}

queue queue_creer(int max) {
   assert(max > 0);
   queue fa;
   fa.capacite = max;
   fa.debut = -1;
   fa.data = malloc(max*sizeof(int));
   return fa;
}

void queue_resize(queue* fa,int max) {
   assert(queue_est_valide(*fa));
   if (max > fa->capacite) {
      fa->capacite = max;
      fa->data = realloc(fa->data,max*sizeof(int));
   }
}

void queue_detruire(queue* fa) {
    fa->capacite = -1;
    fa->debut = -40;
    free(fa->data);
}

void queue_inserer(queue* fa,int val) {
   if (queue_est_pleine(*fa)) {
      queue_resize(fa,fa->capacite+INCR);
   }
   fa->debut++;
   fa->data[fa->debut] = val;
}

int queue_extraire(queue* fa) {
   int val = queue_tete(*fa);
   // à compléter
   return val; 
}

///////////////////// AVEC LES POINTEURS ////////////////////////////

/* Utilité du typedef : Element a; <=> struct Element a; */
typedef struct _element {
   int data;
   struct _element* next;
} element;

typedef struct _queue_ptr {
   element* tete;
   element* debut;
} queue_ptr;

/Creer une nouvelle queue vide
queue queue_creer_ptr() {
   queue fa;
   fa.tete = fa.debut = NULL;
   return fa;
}

void queue_inserer_ptr(queue_ptr* fa,int val) {
   element* elmt = malloc(sizeof(element));
   elmt->data = val;
   elmt->next = NULL;
   if (queue_est_vide_ptr(*fa)) {
      fa->tete = elmt;
   } else {
      fa->debut->next = elmt; 
   }
   fa->debut = elmt;   
}

int queue_extraire_ptr(queue_ptr* fa) {
   int val = queue_tete_ptr(*fa);
   element* elmt = fa->tete;
   fa->tete = fa->tete->next;
   free(elmt);
   if (NULL == fa->tete) {
      fa->debut = NULL;
   } 
   return val;
}

void queue_detruire_ptr(queue_ptr* fa) {
   while(!queue_est_vide_ptr(fa)){
       int val = queue_extraire_ptr(fa);
   }   
}

bool queue_est_vide_ptr(queue_ptr fa) {
   return (NULL == fa.tete && NULL == fa.debut);
}

int queue_tete_ptr(queue_ptr fa) {
   assert(!queue_est_vide_ptr(fa));
   return fa.tete->data;
}

int queue_debut_ptr(queue_ptr fa) {
   assert(!queue_est_vide_ptr(fa));
   return fa.debut->data;
}

int queue_count_ptr(queue_ptr fa) {
   int cnt = 0;
   element *courant = fa;
   while (courant != NULL){
       courant = courant->next;
       cnt++;
   }   
   return cnt;
}