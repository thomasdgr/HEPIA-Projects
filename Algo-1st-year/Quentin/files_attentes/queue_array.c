#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>
#include"queue_array_int.h"

bool queue_est_valide(queue fa) {
   return (fa.capacite > 0 && fa.debut >= -1);
}

bool queue_est_vide(queue fa) {
   assert(queue_est_valide(fa));
   return (-1 == fa.debut);
}

bool queue_est_pleine(queue fa) {
  return fa.debut== fa.capacite-1;
}

int queue_count(queue fa) {
   return fa.debut+1;
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
   // à compléter
}

void queue_inserer(queue* fa,int val) {
   if (queue_est_pleine(*fa)) {
      queue_resize(fa,fa->capacite+100);
   }
   fa->debut++;
   fa->data[fa->debut] = val;
}

int queue_extraire(queue* fa) {
   int val = queue_tete(*fa);
   for(int i=0;i<fa->debut;i++){
     fa->data[i]=fa->data[i+1];
   }
   fa->debut-=1;
   return val;
}
void queue_print(queue fa){
  for(int i=0; i<=fa.debut;i++){
    printf("%d ", fa.data[i]);
  }
  printf("\n");
}
