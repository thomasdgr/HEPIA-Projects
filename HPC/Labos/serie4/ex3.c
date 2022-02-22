#include <mpi.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int const MAX_ARY_SIZE = 10;

// Affiche un tableau (vecteur) d'entiers
void print_ary( int* ary, int n ) {  
  for (int i = 0; i < n; i++) {
    printf("%d ", ary[i]);
  }    
  printf("\n");
}

// Initialise le générateur de nombre aléatoire avec
// une graine différente pour chaque noeud de calcul
void initRndGen( int rank ) {
  srand ( time(NULL) + rank );
}

int* generateAry(int n) {  
  int* ary = malloc(n*sizeof(int));
  for ( int i = 0; i < n; i++ ) {
    ary[i] = i + 1;
  }
  return ary;
}

// temps de sommeil aléatoire entre 1 et 10 secondes
void napTime() {
  int sleepTime = rand() % 10 + 1;    
  sleep( sleepTime );
}

int main(int argc, char **argv) {
  int myRank; 
  int nProc;
 
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &nProc);  
  MPI_Status status;
  initRndGen( myRank );

  if ( myRank == 0 ) {
    // Réception + allocation + affichage
    int tailleRecep;
    
    for (size_t i = 1; i < nProc; i+=1) {
        MPI_Recv(&tailleRecep, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        int *donneRecep = malloc(tailleRecep*sizeof(int));
        MPI_Recv(donneRecep, tailleRecep, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
        print_ary(donneRecep, tailleRecep);
        free(donneRecep);
    }
  }
  else {
    // Création de la donnée
    MPI_Request request;
    int n_elem = MAX_ARY_SIZE;
	int* ary = generateAry(n_elem);
    
    // Envoi de la taille ici
    MPI_Isend(&n_elem, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
    napTime();
    MPI_Wait(&request, &status);
    
    // Envoi de la donnée ici
    MPI_Isend(ary, n_elem, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
    napTime();
    free(ary);
    MPI_Wait(&request, &status);
  }
  
  MPI_Finalize();
}