#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct _element {
   int info;
   struct _element* suivant;
} element;

typedef element* anneau;

anneau init();
bool is_empty(anneau ring);
void insert(anneau* ring, int val);
void move(anneau* ring, int k);
bool search(anneau* ring, int val);
int extract(anneau* ring);
void delete(anneau* ring, int val);
void print(anneau ring);

anneau init() {
   return NULL;
}

void insert(anneau* ring, int val) {
   element* tmp = malloc(sizeof(element));
   tmp->info = val;
   if (is_empty(*ring)) {
      tmp->suivant = tmp;
   } else {
      tmp->suivant = (*ring)->suivant;
   }
   *ring = tmp;
}

bool is_empty(anneau ring) {
   return NULL == ring;
}

int extract(anneau* ring) {
   assert(!is_empty(*ring));
   int val = (*ring)->suivant->info;
   element* tmp = (*ring)->suivant;
   if(tmp->suivant == tmp){
       *ring = NULL;
   } else {
       (*ring)->suivant = tmp->suivant;
   }
   free(tmp);
   return val;
}

void move(anneau* ring, int k) {
   assert(!is_empty(*ring));
   for (int i = 0; i < k; i++){
       *ring = (*ring)->suivant;
   }
}

bool search(anneau* ring, int val) {
   if (!is_empty(*ring)) {
      element* debut = *ring;
      do {
         if ((*ring)->suivant->info == val) {
            return true;
         }
         move(ring, 1);
      } while (*ring != debut);
   }
   return false;
}

void delete(anneau* ring, int val) {
   if (search(ring, val)) {
      extract(ring);
   }
}

void print(anneau ring) {
   if (!is_empty(ring)) {
      element* crt = ring;
      do {
         printf("%d ",crt->info);
         crt = crt->suivant;
      } while (crt != ring);
      printf("\n");
   }
}

void joseph_anneau(anneau* ring, int val) {
   for (int i = 1; i <= val; i++) {
      insert(ring, i);
   }
}

void joseph_extract(anneau* ring, int k) {
   while(!is_empty(*ring)) {
      move(ring, k-1);
      printf("%d\n ",extract(ring));
   }
}

void main(int argc,char** argv) {
   anneau jojo = init();
   int nb1 = 0;
   int nb2 = 0;
   print("entrer un nombre : ");
   scanf("%d",nb1);
   print("\nentrer un autre nombre : ");
   scanf("%d",nb2);
   joseph_insert(&jojo, nb1);
   print(jojo);
   joseph_extract(&jojo, nb2);
   print(jojo);
}

