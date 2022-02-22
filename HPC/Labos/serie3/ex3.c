#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    int rank;
    int new_rank;
    int nProc;
    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
    
    MPI_Status status;
    double starttime, endtime;
    starttime = MPI_Wtime();

    MPI_Comm evenOddComm; // on crée un comm et on lui envoie 1 si le rank du processus est pair, sinon 2
    MPI_Comm_split(MPI_COMM_WORLD, (rank % 2 == 0) ? 1 : 2, nProc, &evenOddComm);
    MPI_Comm_rank(evenOddComm, &new_rank);
    MPI_Bcast(&rank, 1, MPI_INT, 0, evenOddComm);
    MPI_Comm_free(&evenOddComm);

    if(rank == 0){
        endtime = MPI_Wtime();
        printf("N=%d\nP=%d\nTime=%f\n", 0 ,nProc, endtime-starttime);
    }

    MPI_Finalize();
    return 0;
}
