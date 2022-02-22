#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include "bin_tree.h"

static node* position(arbre tree,int cle) {
   node* crt = tree;
   if (NULL != crt) {
      while (cle != crt->key && NULL != crt->child[(cle > crt->key)]) {
         crt = crt->child[(cle > crt->key)];
      }
   }
   return crt;
}

static node* parent(arbre tree,node* nd) {
   assert(NULL != tree && NULL != nd);
   node* parent = NULL;
   int cle = nd->key;
   if (nd != tree) {
      node* crt = tree;
      do  {
          parent = crt;
          crt = crt->child[(cle > crt->key)];
      } while (crt != nd);
   }
   return parent;
}

int arbre_depth(arbre tree) {
   if (NULL == tree) {
      return 0;
   } else {
      return 1+fmax(arbre_depth(tree->child[0]),arbre_depth(tree->child[1]));
   }
}

int arbre_size(arbre tree) {
   if(NULL == tree){
      return 0;
   } else {
     return 1 + arbre_size(tree->child[0]) + arbre_size(tree->child[1]);
   }
}

bool arbre_insert(arbre* tree,int cle) {
   if (NULL == *tree) {
      *tree = calloc(1,sizeof(node));
      (*tree)->key = cle;
   } else {
      node* nd = position(*tree,cle);
      if (cle != nd->key) {
         nd->child[(cle > nd->key)] = calloc(1,sizeof(node));
         nd->child[(cle > nd->key)]->key =  cle;
      } else {
         return false;
      }
   }
   return true;
}

bool arbre_delete(arbre* tree,int cle) {
   node* nd = position(*tree,cle);

   if (NULL == nd || cle != nd->key) {
      return false;
   }

   // noeud terminal
   if (NULL == nd->child[0] && NULL == nd->child[1]) {
      node* nd_parent = parent(*tree,nd);
      nd_parent->child[0] = NULL;
      nd_parent->child[1] = NULL;
      free(nd);
      return true;
   }

   // noeud interne et récursion
   for (int ind=0;ind<2;ind++) {
      if (NULL != nd->child[ind]) {
         node* next = position(nd->child[ind],cle);
         int val = next->key;
         if (NULL == nd->child[ind]->child[ind^1]) {
            nd->child[ind] = next->child[ind];
            free(next);
         } else {
            bool res = arbre_delete(tree,next->key);
         }
         nd->key = val;
         return true;
      }
   }
}

void arbre_print(arbre tree,int N) {
   if (N <= 0) {
      N = 1;
   }
   if (NULL != tree) {
      arbre_print(tree->child[1],N+1);
      for (int i=0;i<N;i++) {
         printf("    ");
      }
      printf("%d\n",tree->key);
      arbre_print(tree->child[0],N+1);
   }
}

bool arbre_search(arbre tree,int cle)
{
  node* crt = tree;
  bool trouve = false;
  while (crt != NULL && !trouve)
  {
    if (cle < crt ->child[0])
    {
      crt = crt ->child[0];
    }
    else if (cle > crt->child[1])
    {
      crt = crt->child[1];
    }
    else
    {
      trouve = true;
    }
  }
  return trouve;
}
