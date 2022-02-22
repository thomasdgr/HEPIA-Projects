#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "AVL.h"

// fonction de rotation à gauche
arbre rot_gauche(arbre P){
   arbre Q = NULL;
   if (NULL != P)
   {
      Q = P->droite;
      P->droite = Q;
      Q->gauche = P;
   }
   return Q;
}

// fonction de rotation à droite (à complété)
arbre rot_droite(arbre P){
   arbre Q = NULL;
   if (NULL != P){
      // bla bla bla ... 
   }
   return Q;
}