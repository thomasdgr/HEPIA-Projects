#ifndef ARRAY_NODE_H_
#define ARRAY_NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// structure d'un élément du fichier
typedef struct node{
    int classe;
    int attributs[6];
    // on skip l'id
} node;

// liste contenant tous les noeuds du fichier
typedef struct arrayNode{
    node* array;
    int length;
} arrayNode;

// liste équivalente à ArrayNode mais avec un seul attribut par noeud
typedef struct single{
    int classe;
    int attribut;
} single;

// création d'une liste de noeud
arrayNode createArrayNode(int length);

// suppression d'une liste de noeud
void freeArrayNode(arrayNode *content);

// affichage d'une liste de noeud
void printArrayNode(arrayNode content);
// affichage v2
void printSingle(single * content, int size);

// retourne un objet single à partir d'un arrayNode
single * nodeColumn(arrayNode content, int index);

// filtre un array node selon la valeur d'un attribut -> utile après avoir coupé sur un attribut à une certaine valeur
arrayNode filter_arrayNode(arrayNode kek, int index_coupe, int new_len, double coupe, bool lower);

#endif
