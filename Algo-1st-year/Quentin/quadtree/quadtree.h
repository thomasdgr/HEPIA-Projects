#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#define CHILDREN 4
typedef struct _node{
  int info;
  struct _node* child[CHILDREN];
}node;

node * tree_create(int depth);
void print_int_tree(node * tree,int depth);
void desalloc_tree(node* tree);
void tree_sum(node * tree);
int tree_depth(node * tree);
node * position(node * tree, int i, int j, int depth);
