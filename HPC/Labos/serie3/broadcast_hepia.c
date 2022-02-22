#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int nProc;

void HEPIA_Bcast(void *data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator){
    for (int i = 0; i < nProc; i++){
        if(i != root){
            MPI_Send(data, count, datatype, i, 666,communicator);
        }
    }
}

int main(int argc, char *argv[]){
    int rank;

    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
    
    MPI_Status status;
    double starttime, endtime;
    starttime = MPI_Wtime();
    
    int M = atoi(argv[1]);
    int *donneEnvoie = malloc(M*sizeof(int));
    int *donneReception = malloc(M*sizeof(int));
    for (size_t i = 0; i < M; i+=1) {
        donneEnvoie[i] = rank;
    }

    if(rank == 0) {
        HEPIA_Bcast(donneEnvoie, M, MPI_INT, rank, MPI_COMM_WORLD);
    }else{
        MPI_Recv(donneReception, M, MPI_INT, 0, 666, MPI_COMM_WORLD, &status);
    }
    
    free(donneEnvoie);
    free(donneReception);
    
    endtime = MPI_Wtime();
    if(rank == nProc-1) printf("N=%d\nP=%d\nTime=%f\n", M ,nProc, endtime-starttime);
    
    MPI_Finalize();
    return 0;
}
