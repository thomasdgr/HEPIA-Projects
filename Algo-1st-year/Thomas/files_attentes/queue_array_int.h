#ifndef QUEUE_ARRAY_INT_H
#define QUEUE_ARRAY_INT_H

#include <stdbool.h>


typedef struct _queue {
   int* data;
   int debut; //tete à l'index 0
   int capacite;
} queue;

//Créer une nouvelle queue vide
queue queue_creer(int max);
//Libérer le tableau, mettre la capacité à < -1
void queue_detruire(queue* fa);
//Inserer un élement en début de queue
void queue_inserer(queue* fa,int val);
//Extraire un élément en tête de queue
int queue_extraire(queue* fa);
//Tester si la queue est valide
bool queue_est_valide(queue fa);
//Tester si la queue est vide
bool queue_est_vide(queue fa);
//Consulter l'élément en tête de queue
int queue_tete(queue fa);
//Consulter l'élément au début de queue
int queue_debut(queue fa);
//Compter du nombre d'éléments de la queue:
int queue_count(queue fa);

void queue_print(queue fa);

#endif
