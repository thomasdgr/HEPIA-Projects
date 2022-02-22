#include <stdio.h>
#include <stdbool.h>
int position(int n, int tab[n], int val){
  int indexF=n-1;
  for(int i=0; i<n-1;i++){
    if(val<tab[i]){
      indexF=i;
      break;
    }
  }
  printf("val:%d indexF: %d\n",val,indexF);
  return indexF;
}
void step(int n, int tab[n]){

  int pos= position(n,tab,tab[n-1]);
  int tmp=tab[n-1];
  for(int i=n-1;i>pos;i--){
    tab[i]=tab[i-1];
  }
  tab[pos]=tmp;
}
void print_tab(int n, int tab[n]){
  for(int i=0;i<n;i++){
    printf("%d ",tab[i]);
  }
  printf("\n");
}
int main(){
  int tab[]={1,8,3,2,4,5,10,2};
  //print_tab(7,tab);
  //printf("Index:%d\n",position(3,tab,3));
  for(int i=1;i<=8;i++)
  {
    step(i,tab);
    printf("i: %d\n",i );
    print_tab(8,tab);
  }
  //print_tab(7,tab);

  return 1;
}
