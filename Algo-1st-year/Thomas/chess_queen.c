#include <stdio.h>
#include <stdlib.h>

typedef enum _piece {SAFE, VULN, QUEEN} piece;

void print(int n,int m,piece board[n][m]) {
   for (int i=n-1;i>=0;i--) {
      printf("%c ",'a'+i);
      for (int j=0;j<m;j++) {
         switch(board[i][j]) {
            case VULN: printf(" *"); break;
            case SAFE : printf(" o"); break;
            case QUEEN: printf(" R");
         }
      }
      printf("\n");
   }
   printf("\n  ");
   for (int j=0;j<m;j++) printf(" %d",j+1);
   printf("\n");
}

void couverture(int n,int m,piece board[n][m],int r_i,int r_j) {
   for (int k=0;k<n;k++) {
      board[k][r_j] = VULN;
   }
   for (int k=0;k<m;k++) { 
      board[r_i][k] = VULN;
      int tmp = r_j-k;
      if (0 <= r_i+tmp && r_i+tmp < n) 
         board[r_i+tmp][k] = VULN; 
      if (0 <= r_i-tmp && r_i-tmp < n) 
         board[r_i-tmp][k] = VULN;
   }
   board[r_i][r_j] = QUEEN;
}

void main() {
   int n=8;
   piece board[n][n];
   for (int i=0;i<n;i++) {
      for (int j=0;j<n;j++) {
         board[i][j] = SAFE;
      }
   }
   print(n,n,board);
   printf("Entrez la ligne de la reine (1..%d): ",n);
   int r_j;
   scanf("%d",&r_j);
   r_j--;
   printf("Entrez la colonne de la reine ('a'..'%c'): ",n-1+'a');
   char ch[1];
   scanf("%s",ch);
   couverture(n,n,board,ch[0]-'a',r_j);
   print(n,n,board);
}
