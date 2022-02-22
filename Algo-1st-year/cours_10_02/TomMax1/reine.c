#include <stdio.h>
#include <stdlib.h>

typedef enum _piece {SAFE, VULN, QUEEN} piece;

void print(int col, int lin, piece tab[col][lin]) {
   for (int i = col - 1; i >=0; i--) {
      printf("%c ",'a'+i);
      for (int j = 0; j < lin; j++) {
         switch(tab[i][j]) {
            case VULN: printf(" *"); break;
            case SAFE : printf(" ."); break;
            case QUEEN: printf(" R");
         }
      }
      printf("\n");
   }
   printf("\n  ");
   for (int j=0;j<lin;j++) printf(" %d",j+1);
   printf("\n");
}

void couverture(int col, int lin, piece tab[col][lin], int Rx, int Ry) {
   for (int i = 0; i < col; i++) {
      tab[i][Ry] = VULN;
   }
   for (int j = 0; j < lin; j++) { 
      tab[Rx][j] = VULN;
      int tmp = Ry-j;
      if (0 <= Rx + tmp && Rx + tmp < col){
         tab[Rx + tmp][j] = VULN; 
      } 
      if (0 <= Rx - tmp && Rx - tmp < col){
         tab[Rx - tmp][j] = VULN;
      } 
   }
   tab[Rx][Ry] = QUEEN;
}

void main() {
   int size = 8;
   piece tab[size][size];
   for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
         tab[i][j] = SAFE;
      }
   }
   print(size,size,tab);
   printf("\nEntrez la ligne de la reine (1..%d): ",size);
   int Rx;
   scanf("%d",&Rx);
   Rx--;
   printf("Entrez la colonne de la reine ('a'..'%c'): ",size-1+'a');
   char Ry[1];
   scanf("%s",Ry);
   couverture(size,size,tab,Ry[0]-'a',Rx);
   print(size,size,tab);
}
