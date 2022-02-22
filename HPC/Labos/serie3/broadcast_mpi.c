#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int rank;
    int nProc;
    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
    
    MPI_Status status;
    double starttime, endtime;
    starttime = MPI_Wtime();
    
    int M = atoi(argv[1]);
    int *donneEnvoie = malloc(M*sizeof(int));
    
    if(rank == 0) {
        for (size_t i = 0; i < M; i+=1) donneEnvoie[i] = rank;
    }
    MPI_Bcast(donneEnvoie, M, MPI_INT, 0, MPI_COMM_WORLD);

    free(donneEnvoie);
    
    if(rank == nProc-1) {
        endtime = MPI_Wtime();
        printf("N=%d\nP=%d\nTime=%f\n", M ,nProc, endtime-starttime);
    }
    
    MPI_Finalize();
    return 0;
}
