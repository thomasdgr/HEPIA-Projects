#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int myRank;
  int nProc;
 
  MPI_Init(&argc, &argv); // initialise les threads
  MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // donne le rang du thread actuel
  MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
 
  printf("Hello, I'm %d out of %d\n", myRank, nProc);
 
  MPI_Finalize(); // termine correctement les threads
}

