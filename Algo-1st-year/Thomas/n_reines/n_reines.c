// Problème des N-reines
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
void board_print(int n, bool **board){
  for(int i=0; i<n;i++){
    for(int j=0; j<n;j++){
      printf("%d ",board[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
// Alloue un tableau de dimension nxn de booléens dont le contenu est true
bool** board_alloc(int n) {
if(n>0){
  bool **board= malloc(sizeof(bool*)*n);
  bool *bande = malloc(sizeof(bool)*n*n);
  int cprP=0;
  int cprT=0;
   while(cprP<n){
     board[cprP]=&bande[cprT];
     cprP++;
     cprT+=n;
   }
   for(int i=0; i<n*n;i++){
     board[0][i]=1;
   }
   return board;
 }else{
   return NULL;
 }
}

// Désalloue un tableau de dimension nxn de booléens
void board_free(int n,bool** tab) {
   free(tab[0]);
   free(tab);
}

// Retourne un clone de <board>
bool** clone(int n,bool** board) {
   bool **clone = board_alloc(n);
   for(int i=0; i<n;i++){
     for(int j=0; j<n;j++){
       clone[i][j]=board[i][j];
     }
   }
   board_print(8,board);
   return clone;
}

// Retourne une copie du tableau <board> complété avec les positions
// prises sur la droite droite par une reine placée en <board(li,co)>
bool** prises_devant(int n,bool** board,int li,int co) {
  //board_print(8,board);
   bool** cases_prises = clone(n,board);
   //board_print(8,cases_prises);
   int cprli=li;
   int cprco=co;
   for(int i=0;i<n;i++){
     cases_prises[i][co]=0;
   }
   for(int j=co;j<n;j++){
     cases_prises[li][j]=0;
   }
   while(cprli>0 && cprco<7){
     cprli--;
     cprco++;
     cases_prises[cprli][cprco]=0;
   }
   cprli=li;
   cprco=co;
   while(cprli<7 && cprco<7){
     cprli++;
     cprco++;
     cases_prises[cprli][cprco]=0;

   }
   cases_prises[li][co]=0;
   //printf("l:%d\n",li);
   //board_print(n,cases_prises);
   return cases_prises;
}

// Calcule le nombre de solutions au problème des <N> reines
void nb_sol(int n,bool** board,int co, int* ptr_cpt) {
   for (int li=0;li<n;li++) {
      if (board[li][co]) {
        if(co==n-1)
          *ptr_cpt = (*ptr_cpt)+1;
         if (co <= n-1) {
            bool** tab = prises_devant(n,board,li,co);
            nb_sol(n,tab,co+1,ptr_cpt);
            board_free(n,tab);
         }
    }
 }
}
void main() {
   int n = 8;
   // échiquier où placer les reines
   bool** board = board_alloc(n);
   board= prises_devant(8,board, 0,0);
   board= prises_devant(8,board, 7,1);
   //printf("Copy\n");
   //bool **test =clone(8,board);
   //test=prises_devant(8,board, 5,5);
   board_print(8,board);
   //board_print(8,test);
   //compteur du nombre de solutions au problème des <N> reines
   int cpt = 0;
   //nb_sol(n,board,0,&cpt);
   printf("Nombre de solutions: %d\n",cpt);
}
