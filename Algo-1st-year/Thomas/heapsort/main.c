#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
void print_tab(int size, int tab[size]){
  for(int i=0; i<size;i++){
    printf("%d ", tab[i]);
  }
  printf("\n");
}
int ind_fils_gauche(int indPere){
  return indPere*2 +1;
}
int ind_fils_droit(int indPere){
  return indPere*2 +2;
}
void swap(int * a1, int * a2){
  if(a1!= NULL && a2!= NULL && a1!=a2){
    int tmp= *a1;
    *a1= *a2;
    *a2= tmp;
  }
}
int indice_max(int size, int tab[size], int indice1, int indice2, int indice3){
  int indMax=indice1;
  if(indice3<size){
    if(tab[indice3]>tab[indice2]){
      indMax=indice3;
    }
  }

  if(indice2<size){
    if(tab[indice2]>tab[indice3])
    {
      indMax=indice2;
    }
  }

  if(tab[indMax]<=tab[indice1]){
    indMax=indice1;
  }
  return indMax;
}
bool ind_test_overflow(int size, int indPromotion){
  int indGauche= ind_fils_gauche(indPromotion);
  int indDroit= ind_fils_droit(indPromotion);
  return (indGauche >=size || indDroit>=size);
}
int promotion(int size, int tab[size],int indPromotion){
    int indGauche= ind_fils_gauche(indPromotion);
    int indDroit= ind_fils_droit(indPromotion);

    int valFilsGauche = tab[indGauche];
    int valFilsDroit = tab[indDroit];
    int indValMax= indice_max(size, tab, indPromotion,indGauche, indDroit);
    if(indPromotion!= indValMax){
      swap(&tab[indValMax], &tab[indPromotion]);
      promotion(size, tab, indValMax);
    }

}
int entassement(int size, int tab[size]){
  for(int i=(size/2)-1;i>=0;i--){
    promotion(size, tab, i);
  }
}
int heapsort(int size, int tab[size]){
  entassement(size, tab);
  int newSize=size-1;
  swap(&tab[0],&tab[size-1]);
  while(newSize>2){
    promotion(newSize,tab, 0);
    swap(&tab[0],&tab[newSize-1]);
    print_tab(size,tab);
    newSize-=1;
  }
}
int main(){
  int tab[]= {1,10,4,8,20,11,15,19,2,7};
  print_tab(10,tab);
  heapsort(10,tab);
  print_tab(10,tab);
}
