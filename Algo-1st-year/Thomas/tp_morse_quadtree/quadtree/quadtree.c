#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "matrix.h"
#include "pgm.h"
#include <string.h>
#include <math.h>
#define CHILDREN 4

typedef struct _node
{
   double moyen2, moyenne;
   struct _node* child[CHILDREN];
} node;

bool is_leaf(node* nd) {
  for (int i = 0; i < CHILDREN; i++)
  {
    if (nd->child[i] != NULL) return false;
  }
  return true;
}

node* node_create()
{
   node* a = calloc(1,sizeof(node));
   return a;
}

node* tree_create(int depth)
{
   node* a = node_create();
   if (depth > 0) {
      for (int i=0;i<CHILDREN;i++) {
         a->child[i] = tree_create(depth-1);
      }
   }
   return a;
}

int max(int x,int y) { return  (x >= y ? x : y); }

int depth(node* a)
{
   int p[CHILDREN];
   memset(p,0,CHILDREN*sizeof(int));
   if (is_leaf(a)) {
      return 0;
   } else {
      for (int i=0;i<CHILDREN;i++) {
         p[i] = depth(a->child[i]);
      }
      int m = p[0];
      for (int i=1;i<CHILDREN;i++) {
         m = max(m,p[i]);
      }
      return 1+m;
   }
}

void print(node* arbre,int decal,char* sep)
{
   if (NULL != arbre) {
      for (int i=0;i<decal;i++) {
         printf("%s",sep);
      }
      printf("%f %f\n",arbre->moyenne,arbre->moyen2);

      decal++;
      if (!is_leaf(arbre)) {
         for (int i=0;i<CHILDREN;i++) {
            print(arbre->child[i],decal,sep);
         }
      }
   }
}

// Fonction utile pour les symétries
void swap(void** ptr1,void** ptr2)
{
   void* tmp = *ptr1;
   *ptr1 = *ptr2;
   *ptr2 = tmp;
}

node* position(int li,int col,node* a,int d)
{
   node* crt = a;
   int li_start = 0;
   int col_start = 0;
   int index = 2*(li >= pow(2,d))+(col >= pow(2,d));

   while (NULL != crt->child[index])
   {
      crt = crt->child[index];
      li_start += (index/2==1)*pow(2,d);
      col_start += (index%2==1)*pow(2,d);
      d--;
      index = 2*(li-li_start >= pow(2,d)) + (col-col_start >= pow(2,d));
   }
   return crt;
}

void matrix2tree(matrix *mat,node* arbre, bool m2t)
{
   int d = depth(arbre)-1;
   for (int li=0;li<mat->m;li++) {
      for (int co=0;co<mat->n;co++) {
         node* crt = position(li,co,arbre,d);
         if (m2t){
           crt->moyenne = mat->data[li][co];
           crt->moyen2 = pow(mat->data[li][co],2);
         }
         else mat->data[li][co] = crt->moyenne;
      }
   }
}

void free_arbre(node ** quadtree)
{
  if(is_leaf(*quadtree))
  {
    free(*quadtree);
    *quadtree= NULL;
  }
  else
  {
    for (int i=0;i<CHILDREN;i++) free_arbre(&((*quadtree)->child[i]));
    free(*quadtree);
    *quadtree = NULL;
  }
}


void moyenne_moye2(node *arbre)
{
  if (!is_leaf(arbre)) {
    for (int i=0;i<CHILDREN;i++) {
       moyenne_moye2(arbre->child[i]);
    }
    for (int i = 0; i < CHILDREN; i++)
    {
      arbre->moyenne += arbre->child[i]->moyenne;
      arbre->moyen2 += arbre->child[i]->moyen2;
    }
    arbre->moyenne /= CHILDREN;
    arbre->moyen2 /= CHILDREN;
  }
}

void compression(node* arbre, double seuil)
{
   if (!is_leaf(arbre)) {
      for (int i=0;i<CHILDREN;i++) {
         compression(arbre->child[i], seuil);
      }
      bool last_branch = true;
      for (int i=0;i<CHILDREN;i++) {
         if(!is_leaf(arbre->child[i])) last_branch = false;
      }
      double ecart_ty = sqrt(arbre->moyen2 - pow(arbre->moyenne,2));
      if(last_branch && ecart_ty < seuil)
      {
        for (int i = 0; i < CHILDREN; i++) {
          free_arbre(&((*arbre).child[i]));
        }
      }
   }
 }
 void max_tree(node* arbre, double *v_max)
 {
   if (NULL != arbre) {
      if (!is_leaf(arbre)) {
         for (int i=0;i<CHILDREN;i++) {
            max_tree(arbre->child[i], v_max);
         }
      }
      else
      {if (*v_max <= arbre->moyenne) *v_max = arbre->moyenne;}
   }
}

int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    pgm fichier_extrait = pgm_read(argv[1]);
    double seuil = atof(argv[2]);
    node *quadtree = tree_create(log2(fichier_extrait.mat.n));
    pgm fichier_out;
    fichier_out.mat = matrix_create(fichier_extrait.mat.n,fichier_extrait.mat.n);

    matrix2tree(&fichier_extrait.mat, quadtree, true);
    pgm_destroy(&fichier_extrait);
    moyenne_moye2(quadtree);

    compression(quadtree, seuil);

    double v_max = 0;
    max_tree(quadtree,  &v_max);

    matrix2tree(&fichier_out.mat, quadtree, false);
    fichier_out.max = v_max;
    free_arbre(&quadtree);

    pgm_write("out", fichier_out);
    pgm_destroy(&fichier_out);
    return 0;
  }
}
