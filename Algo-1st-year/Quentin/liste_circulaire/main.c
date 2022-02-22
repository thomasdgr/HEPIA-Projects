#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct _element {
   int info;
   struct _element* next;
} element;

typedef element* anneau;
void affichage(anneau listeCirc){
  if(listeCirc!=NULL){
    element* ptrCourant= listeCirc;
    do{
      printf("%d\n", ptrCourant->info);
      ptrCourant= ptrCourant->next;
      //printf("%p\n", ptrCourant);
    }while(ptrCourant!=listeCirc);
  }
}
int insertion(anneau* ptrlisteCirc){
  element* newElem= malloc(sizeof(element));
  if(*ptrlisteCirc==NULL){
    printf("ok\n");
    newElem->info=1;
    newElem->next=newElem;
    printf("%p\n",newElem);

  }else{
    newElem->info= (*ptrlisteCirc)->info +1;
    newElem->next=(*ptrlisteCirc)->next;
    (*ptrlisteCirc)->next=newElem;
    printf("Pas null\n");
  }
  *ptrlisteCirc=newElem;
}
element* creation(int nombreElements){
  element* liste=NULL;
  for(int i=0; i<nombreElements;i++){
    insertion(&liste);
  }
  return liste;

}
int move(anneau* ptrlisteCirc,int k){
  for(int i=1; i<=k-1;i++){
    *ptrlisteCirc=(*ptrlisteCirc)->next;
  }
}
int extraction_joseph(anneau* ptrlisteCirc,int k){
  while((*ptrlisteCirc)!=NULL){
    move(ptrlisteCirc,k);
    element* tmp= (*ptrlisteCirc)->next;
    printf("supprimé: %d\n",tmp->info);
    (*ptrlisteCirc)->next= (*ptrlisteCirc)->next->next;
    if((*ptrlisteCirc)==(*ptrlisteCirc)->next){
      printf("supprimé: %d\n",(*ptrlisteCirc)->info);
      (*ptrlisteCirc)=NULL;
    }
    free(tmp);
    tmp=NULL;
  }

}
int main(){

  anneau liste=creation(8);
  extraction_joseph(&liste,3);
  affichage(liste);
  //printf("%d\n", liste->info);
  //move(&liste,3);
  //printf("%d\n", liste->info);
  //printf("%d\n", liste->next->info);
  return 1;
}
