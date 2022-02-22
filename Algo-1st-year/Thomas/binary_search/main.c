#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct _node{
  int info;
  struct _node * tab[2];
} node;
typedef node * arbre;

void print_arbre(arbre tree, int decalage){
  if(tree!=NULL){
    print_arbre(tree->tab[1],decalage+1);
    for(int i=1;i<=decalage;i++){
      printf(" ");
    }
    printf("%d\n",tree->info);
    print_arbre(tree->tab[0], decalage+1);
  }
}
node * parent(arbre tree, int nombre){
  node * ptrCourant = tree;
  //bool trouve=false;
  while(ptrCourant->tab[nombre>(ptrCourant->info)] != NULL
          && (ptrCourant->tab[nombre>(ptrCourant->info)])->info!=nombre)
  {
    ptrCourant= ptrCourant->tab[nombre>(ptrCourant->info)];
  }

  return ptrCourant;
}
bool insert(arbre * parbre, int nombre){

  if(*parbre==NULL){
    (*parbre)= calloc(1,sizeof(node));
    (*parbre)->info=nombre;

  }else{
    node * posInsert= parent(*parbre,nombre);
    //printf("%p",posInsert);
    node * newElement= calloc(1,sizeof(node));
    newElement->tab[0]= NULL;
    newElement->tab[1]=NULL;
    newElement->info= nombre;
    posInsert->tab[nombre>posInsert->info]= newElement;

  }
  return true;
}
node * fils_from_parent(arbre tree, int nombre){
  return tree->tab[nombre>(tree->info)];
}
bool delete( arbre* parbre, int nombre){
  node *posParentDel= parent(*parbre, nombre);
  printf("ptrc:%p\n",posParentDel);
  node *filsDel= fils_from_parent(posParentDel, nombre);
  if(filsDel!=NULL){
    if(filsDel->info!=nombre){
      return 0;
    }
  }else{
    return 0;
  }
  printf("val: %d\n",filsDel->info);
  if(filsDel->tab[0]== NULL && filsDel->tab[1]== NULL ){
    filsDel->info= 0;
    free(filsDel);
    filsDel=NULL;
    posParentDel->tab[nombre>(posParentDel->info)]=NULL;
  }else{
    node * tmpDel= filsDel;
    node * newFils;
    if(filsDel->tab[0]==NULL)
    {
      newFils= filsDel->tab[1];
      tmpDel->info=0;
      free(tmpDel);
      posParentDel->tab[nombre>(posParentDel->info)] = newFils;
    }
    else if(filsDel->tab[1]==NULL)
    {
      newFils= filsDel->tab[0];
      tmpDel->info=0;
      free(tmpDel);
      posParentDel->tab[nombre>(posParentDel->info)] = newFils;
    }
    else if(filsDel->tab[0]!=NULL && filsDel->tab[1]!=NULL){

      newFils= parent(filsDel,nombre);
      int infoProche=newFils->info;
      delete(parbre, infoProche);
      filsDel->info= infoProche;
      //printf("value %d\n", newFils->info);

      //filsDel->info=newFils->info;
      //newFils->info=tmpValue;
    }

  }
}
int main(){
  node * my_arbre = NULL;
  insert( &my_arbre, 14);
  print_arbre(my_arbre,1);
  printf("------\n");
 insert( &my_arbre, 17);
 printf("------\n");
  print_arbre(my_arbre,1);

  insert( &my_arbre, 20);
  printf("------\n");
  print_arbre(my_arbre,1);

  insert( &my_arbre, 21);
  printf("------\n");
  print_arbre(my_arbre,1);
  insert( &my_arbre, 15);
  printf("------\n");
  print_arbre(my_arbre,1);

  insert( &my_arbre, 16);
  printf("------\n");
  print_arbre(my_arbre,1);
  insert( &my_arbre, 4);
  printf("------\n");
  print_arbre(my_arbre,1);
  insert( &my_arbre, 12);
  printf("------\n");
  print_arbre(my_arbre,1);
  insert( &my_arbre, 5);
  printf("------\n");
  print_arbre(my_arbre,1);

  delete(&my_arbre,17);
  printf("------\n");
  print_arbre(my_arbre,1);

  /*delete(&my_arbre,7);
  printf("------\n");
  print_arbre(my_arbre,1);

  delete(&my_arbre,5);
  printf("------\n");
  print_arbre(my_arbre,1);
*/




  /*delete(&my_arbre,8);
  printf("------\n");
  print_arbre(my_arbre,1);

  delete(&my_arbre,7);
  printf("------\n");
  print_arbre(my_arbre,1);

  delete(&my_arbre,5);
  printf("------\n");
  print_arbre(my_arbre,1);*/




/*node arbre1;
arbre1.info =1;
node arbre2;
arbre2.info =2;
arbre2.tab[0]= NULL;
arbre2.tab[1] = NULL;
node arbre3;
arbre3.tab[0]= NULL;
arbre3.tab[1] = NULL;
arbre3.info =3;
arbre1.tab[0]= &arbre2;
arbre1.tab[1] = &arbre3;

node arbre4;
arbre3.tab[1]= &arbre4;
arbre4.tab[1] = NULL;
arbre4.tab[0] = NULL;
arbre4.info =4;
print_arbre(&arbre1,1);*/
}
