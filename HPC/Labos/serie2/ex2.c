#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int myRank;
    int nProc;

    int nb;
    
    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
    
    MPI_Status status;
    if(myRank == 0){
        nb = 420;
        MPI_Send(&nb, 1, MPI_INT, myRank+1, 666, MPI_COMM_WORLD);
        MPI_Recv(&nb, 1, MPI_INT, nProc-1, 666, MPI_COMM_WORLD, &status);
        printf("Process %d received number %d from process %d\n", myRank, nb, nProc);
    } else {
        MPI_Recv(&nb, 1, MPI_INT, (myRank-1) % nProc, 666, MPI_COMM_WORLD, &status);
        printf("Process %d received number %d from process %d\n", myRank, nb, (myRank-1) % nProc);
        MPI_Send(&nb, 1, MPI_INT, (myRank+1) % nProc, 666, MPI_COMM_WORLD);   
    }
    
    MPI_Finalize(); // termine correctement les threads
}
