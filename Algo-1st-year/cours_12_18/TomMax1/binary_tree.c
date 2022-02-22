#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node {
    int info;
    node * sag; // sous arbre gauche
    node * sad; // sous arbre droit
} node;

typedef node* arbre;

// cas de l'expression infixe
void imprime(arbre tree){
    if (NULL != tree){
        imprime(tree->sag);
        printf("%d", tree->info); //racine
        imprime(tree->sad);
    }
}