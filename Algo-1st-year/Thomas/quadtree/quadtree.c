#include "quadtree.h"
node * node_create(){
  return calloc(1,sizeof(node));
}
node * tree_create(int depth){
  node * element = node_create();
  if(depth==0){
    element->info = rand()%100;
  }else{
    element->info= 0;
  }

  if(depth>0){
    for(int i=0; i<CHILDREN;i++){
      element->child[i] = tree_create(depth-1);
    }
  }

  return element;

}

void print_int_tree(node * tree,int depth){
  if(tree!=NULL){
    for(int i=0; i<depth;i++){
      printf(" ");
    }
    printf("%d\n", tree->info);
    for(int i=0; i<CHILDREN;i++)
      print_int_tree(tree->child[i],depth+1);
  }

}

void desalloc_tree(node* tree){
  if(tree->child[0]!=NULL){
    for(int i=0; i<CHILDREN;i++)
      desalloc_tree(tree->child[i]);
    for(int i=0; i<CHILDREN;i++){
      free(tree->child[i]);
      tree->child[i]=NULL;
    }


  }

}
void tree_sum(node * tree){
  if(tree->child[0]!=NULL){
    for(int i=0; i<CHILDREN;i++)
      tree_sum(tree->child[i]);
    tree->info = tree->child[0]->info + tree->child[1]->info + tree->child[2]->info + tree->child[3]->info;
  }
}
int max4(int val0, int val1, int val2, int val3){
  int valMax=val0;
  if(val1>val0)
    valMax=val1;
  if(val2>val1)
    valMax=val2;
  if(val3>val2)
    valMax=val3;
  return valMax;
}
int tree_depth(node * tree){
  int valMax=0;
  if(tree->child[0]== NULL)
    return 0;
  else
    return 1 + max4(tree_depth(tree->child[0]), tree_depth(tree->child[1]), tree_depth(tree->child[2]) ,tree_depth(tree->child[3]));
}
int quadrant(bool successI, bool successJ){
  if(successI==false && successJ==false)
    return 0;
  else if(successI==false && successJ==true)
    return 1;
  else if(successI==true && successJ==false)
    return 2;
  else if(successI==true && successJ==true)
    return 3;
}
node * position(node * tree, int i, int j, int depth){
  node * ptrCourant= tree;
  bool supMiddleI =  i>=pow(2,depth-1);
  bool suppMiddleJ= j>=pow(2,depth-1);
  int quadrantSel= quadrant(supMiddleI,suppMiddleJ);
  int ScaleValuePow=0;
  while(ptrCourant->child[0]!=NULL){
    ptrCourant = ptrCourant->child[quadrantSel];
    depth--;
    ScaleValuePow++;
    supMiddleI = i-pow(2,ScaleValuePow)>=pow(2,depth-1);
    suppMiddleJ= j-pow(2,ScaleValuePow)>=pow(2,depth-1);
  }
  return ptrCourant;

}
