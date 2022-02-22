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
void bulles_step(int n, int tab[n])
{
  for(int i=0;i<n-1;i++)
  {
    if(tab[i]>tab[i+1])
    {
      swap(&tab[i],&tab[i+1]);
    }
  }
}

void main()
{
  int tableau[]={4,7,6,1,2};
  int tailleTableau=5;
  for(int i=tailleTableau;i>1;i--)
  {
    bulles_step(i,tableau);
    printTab(5,tableau);
  }
  //bulles_step(5,tableau);

}
