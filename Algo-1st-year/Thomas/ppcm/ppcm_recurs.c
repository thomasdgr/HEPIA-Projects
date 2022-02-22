#include <stdio.h>
#include <stdbool.h>
int ppcm(int n, int m, int ni, int mi){
  if(m==n){
    return n;
  }
  else{

    if(n>m){
      m+=mi;
    }else{
      n+=ni;
    }
    printf("n:%d,m:%d\n",n,m);
    ppcm(n,m,ni,mi);
  }
}
int puissance(int a, int p){
  if(p==1){
    return a;
  }else{
    if(p%2==0){
      return puissance(a,p/2)*puissance(a,p/2);
    }else{
      return puissance(a,p-1)*puissance(a,1);
    }
  }
}
int factorielle(int n){
  if(n==0 || n==1){
    return 1;
  }else{
    return n*factorielle(n-1);
  }
}
void CribleEratosthene(int n, bool tab[n]){
  for(int i=0; i<n;i++){
    if(tab[i]==0){
      for(int j=0;j<n;j++){
        if((j+2)%(i+2)==0){
          tab[j]=1;
        }
      }
      tab[i]=0;
    }
  }
}




int main(){
  printf("Resultat PPCM:%d\n",ppcm(2,7,2,7));
  printf("Resultat Factorielle:%d\n",factorielle(5));
  printf("Resultat Puissance:%d\n",puissance(5,3));
  bool tab[99];
  for(int i=0;i<99;i++){
    tab[i]=0;
  }
  for(int i=0;i<99;i++){
    printf("%d ",tab[i]);
  }
  printf("\n");
  CribleEratosthene(99, tab);
  for(int i=0;i<99;i++){
    printf("%d ",tab[i]);
  }

  return 1;
}
