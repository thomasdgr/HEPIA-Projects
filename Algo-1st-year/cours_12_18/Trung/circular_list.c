#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "circular_list.h"

anneau init() {
   return NULL;
}

bool is_empty(anneau ring) {
   return NULL == ring;
}

void insert(anneau* ring,int val) {
   element* tmp = malloc(sizeof(element));
   tmp->info = val;
   if (is_empty(*ring)) {
      tmp->suivant = tmp;
   } else {
      tmp->suivant = (*ring)->suivant;
      (*ring)->suivant = tmp;
   }
   *ring = tmp;
}

int extract(anneau* ring)
{
  if(!is_empty(*ring))
  {
    int a = 0;
    element* tmp = malloc(sizeof(element));
    tmp = (*ring)->suivant;
    a = tmp->info;
    if (tmp == (*ring))
    {
      (*ring) = NULL;
      free(tmp);
      return a;
    }
    (*ring)->suivant = tmp->suivant;
    free(tmp);
    return a;
  }
  return 0;
}

void move(anneau* ring,int k)
{
  if(!is_empty(*ring))
  {
    for (int i = 0; i < k; i++)
    {
      *ring = (*ring)->suivant;
    }
  }
}

bool search(anneau* ring,int val) {
   if (!is_empty(*ring)) {
      element* debut = *ring;
      do {
         if ((*ring)->suivant->info == val) {
            return true;
         }
         move(ring,1);
      } while (*ring != debut);
   }
   return false;
}

void delete(anneau* ring,int val) {
   if (search(ring,val)) {
      extract(ring);
   }
}

void println(anneau ring) {
   if (!is_empty(ring)) {
      element* crt = ring;
      do {
         printf("%d ",crt->info);
         crt = crt->suivant;
      } while (crt != ring);
      printf("\n");
   }
}

bool ispresent(anneau annu, int val)
{
  if (!is_empty(annu))
  {
     element* crt = annu;
     do {
        if (crt->info == val)
        {
          return true;
        }
        crt = crt->suivant;
     } while (crt != annu);
     return false;
  }
  return false;
}
