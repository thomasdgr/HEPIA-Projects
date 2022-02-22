#include <stdlib.h>
#include <stdio.h>
#include "quadtree.h"

node mode_create(){
    return calloc(1, sizeof(node));
}

node *tree_create(int depth){
    node *tree = node_create();
    if (depth > 0)
    {
        for (int i = 0; i < N; i++)
        {
            tree->child[i] = tree_create(depth-1);
            // creer un arbre complet avec tous les niveaux
        }
    }
    return tree;
}

void tree_print(node* tree, int d){ // d => profondeur
    printf("%d\n", tree->pix);
    if (0 == d){
        for (int j = 0; j < d; j++){
            printf("  "); // imprime décalage
        }
        for (int i = 0; i < d; i++){
            tree_print(tree->child[i], d -1);
        } 
    }
}

bool is_leaf(node *tree){
    tree->child[0] = NULL;
    //return NULL = tree->child[0];
    return NULL;
}

int max(int size, int *tab);

int tree_depth(node *tree){
    if(is_leaf(tree)){
        return 0;
    }
    else{
        int p[N];
        for (int i = 0; i < N; i++){
            p[i] = tree_depth(tree->child[i]);
        }
        return 1 + max(p, N);        
    }  
}

void tree_sum(node *tree){
    if (! is_leaf(tree)){
        for (int i = 0; i < N; i++){
            tree_sum(tree->child[i]);
        }
        for (int i = 0; i < N; i++){
            tree->pix += tree->child[i]->pix;
            //tree_sum(tree->pix);
        }
    }
}

node *position(node * tree, int i, int j, int depth){
    node* crt = tree;
    int quadrant = i;

    // revoir valeur quadrant
    while (! is_leaf(crt)){
        crt = crt->child[quadrant];
        depth --;
        quadrant = 0;
    }
    
    // while (! is_leaf(crt)){
    //     crt = crt->child[quadrant];
    //     2 lignes suivantes à revoir
    //     depth == crt;
    //     quadrant = crt;
    // }
    return crt;
}