#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int myRank;
  int nProc;
 
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &nProc);
 
  // initialise un vecteur de taille 10 dont chaque
  // composante vaut myRank
  const int n = 10;
  int* v = malloc(n*sizeof(int));
  for (int i = 0; i < n; ++i) {
      v[i] = myRank;
  }  

  int sum = 0;
  for (int i = 0; i < n; ++i) {
      sum += v[i];
  }

  if (myRank % 2 == 0) {
    printf("I'm process %d", myRank);
    printf(", and the local sum is %d\n", sum);
  }

  free(v);
  MPI_Finalize();
}
