#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#ifndef AVL_H
#define AVL_H

// structure d'un arbre AVL
typedef struct{
    int cle;
    struct _node *gauche, *droite;
    int facteur;
} node;
typedef node* arbre;

// structure de noeud AVL
struct node{
    int key;
    node *sag;
    node *sad;
    int hd, hg; // ce qui change d'un arbre ordinaire
};

// fonction de rotation à gauche et droite
arbre rot_gauche(arbre P);
arbre rot_droite(arbre P)