#include <stdio.h>
#include <stdlib.h>
#include "hachage.h"
#include "string.h"

int main()
{
  annuaire a = annuaire_init(10);
  personne f = {"jean", 2};
  personne q = {"tan", 2};
  personne r = {"hh", 2};
  personne g = {"an", 2};
  personne j = {"treung", 2};
  annuaire_insert(&a,f);
  annuaire_insert(&a,q);
  annuaire_insert(&a,r);
  annuaire_insert(&a,g);
  annuaire_insert(&a,j);
  affichage(a);
  printf("-------------------------------\n" );
  annuaire_remove(&a,f.nom);
  annuaire_remove(&a,q.nom);
  annuaire_remove(&a,r.nom);
  annuaire_remove(&a,g.nom);
  annuaire_remove(&a,j.nom);
  printf("-------------------------------\n" );
  personne k = {"ff", 2};
  personne u = {"hhaaa", 2};
  personne z = {"qq", 2};
  personne i = {" bb", 2};
  personne e = {"treydfadafung", 2};
  annuaire_insert(&a,k);
  annuaire_insert(&a,u);
  annuaire_insert(&a,z);
  annuaire_insert(&a,i);
  annuaire_insert(&a,e);
  affichage(a);

  annuaire_free(&a);
  return 0;
}
