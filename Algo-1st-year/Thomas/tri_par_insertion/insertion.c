#include <stdio.h>
#include <stdlib.h>
void printTab(int n,int tab[n])
{
  for(int i=0; i<n;i++)
  {
    printf("%d ",tab[i]);
  }
  printf("\n");
}
void swap(int *adresse1, int *adresse2)
{
  int varTemp= *adresse1;
  *adresse1= *adresse2;
  *adresse2= varTemp;
}
/*void bulles_step(int n, int tab[n])
{
  for(int i=0;i<n-1;i++)
  {
    if(tab[i]>tab[i+1])
    {
      swap(&tab[i],&tab[i+1]);
    }
  }
}*/
void shift(int *adresse1, int *adresse2)
{
    int nombreTemporaire=*adresse1;
    *adresse1=*adresse2;
    *adresse2=nombreTemporaire;
}
void bulles_step(int n, int tab[n])
{
  int nombreDeplacement=tab[n];
  int nombreTemporaire=0;
  for(int i=n;i>=1;i--)
  {
    if(tab[i]<tab[i-1])
    {
      shift(&tab[i],&tab[i-1]);
    }
  }

}

void main()
{
  int tableau[]={7,4,5,8,6};
  int tailleTableau=5;
  for(int i=1;i<tailleTableau;i++)
  {
    bulles_step(i,tableau);
      printTab(5,tableau);
  }
  //int position=positionNombre(2,tableau);
  //shift(1,tableau);
  //printf("Position: %d\n", position);


  /*for(int i=tailleTableau;i>1;i--)
  {
    bulles_step(i,tableau);
    printTab(5,tableau);
  }*/
  //bulles_step(5,tableau);

}
