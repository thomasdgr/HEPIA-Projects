#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

const int N = 4;
typedef struct _node{
    int pix;
    node* child[N];
}node;

node mode_create();
node *tree_create(int depth);

void tree_print(node* tree, int d);
bool is_leaf(node *tree);
int max(int size, int *tab);
int tree_depth(node *tree);
void tree_sum(node *tree);
node *position(node * tree, int i, int j, int depth);

#endif