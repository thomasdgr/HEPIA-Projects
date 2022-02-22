#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Alloue un tableau de dimension nxn de booléens dont le contenu est true
bool** board_alloc(int n) {
  bool tab;
  tab = malloc(m * sizeof(double*));
  tab[0]= malloc(n * n * sizeof(double));
  for (int i = 0; i < n; i++) {
    tab[i] = tab[0] + i * n;
    for (int j = 0; j < n; j++) {
      tab[i][j] = true;
    }
  }
   return NULL;
}

// Désalloue un tableau de dimension nxn de booléens
void board_free(int n,bool** tab) {
  free(tab[n]);
  free(tab);
}

// Retourne un clone de <board>
bool** clone(int n,bool** board) {
  bool tab_clone = board_alloc(n);

 for(int i = 0; i < n; i++) {
   for(int j = 0; j < n; k++) {
     tab_clone[i][j] = tab[i][j];
   }
 }
 return mat_clone;
}

// Retourne une copie du tableau <board> complété avec les positions
// prises sur la droite droite par une reine placée en <board(li,co)>
bool** prises_devant(int n,bool** board,int li,int co) {
   bool** cases_prises = clone(n,board);
   // à compléter!!!!
   return cases_prises;
}

// Calcule le nombre de solutions au problème des <N> reines
void nb_sol(int n,bool** board,int co, int* ptr_cpt) {
   for (int li=0;li<n;li++) {
      if (board[li][co]) {
         if (co < n-1) {
            bool** tab = prises_devant(n,board,li,co);
            nb_sol(n,tab,co+1,ptr_cpt);
            board_free(n,tab);
         } else {
            *ptr_cpt = (*ptr_cpt)+1;
         }
      }
   }
}

void main() {
   int n = 8;
   // échiquier où placer les reines
   bool** board = board_alloc(n);
   // compteur du nombre de solutions au problème des <N> reines
   int cpt = 0;
   nb_sol(n,board,0,&cpt);
   printf("Nombre de solutions: %d\n",cpt);
}
