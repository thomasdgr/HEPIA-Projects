#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int nombre_minimum(int n, int tab[n], int iDebut){
  int imin=iDebut;
  for(int i=iDebut;i<n;i++){
    if(tab[i]<tab[imin]){
      imin=i;
    }
  }
  return imin;
}
void swap(int *a1, int *a2){
  int tmp=*a1;
  *a1= *a2;
  *a2=tmp;
}
int main(){
  int tableau[]={4,3,1,5,7,6};
  int taille=6;
  for(int i=0;i<taille;i++){
    int indexMin=nombre_minimum(taille, tableau, i);
    printf("%d indexMin:%d\n",tableau[i],indexMin);
    //break;

    swap(&tableau[i],&tableau[indexMin]);

    for(int i=0; i<taille;i++){
      printf("%d ",tableau[i]);
    }
    printf("\n");
  }

  return 0;
}
