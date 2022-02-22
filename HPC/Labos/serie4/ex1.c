#include <mpi.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int myRank;
    int nProc;
    const int nbEnvois = 8;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);

    assert(nProc==2);

    int size = 1;
    for (int iSize = 1; iSize < nbEnvois; ++iSize) {
        int* dummyBuffer = malloc(size*sizeof(int));

        if (myRank == 0) {
            printf("Envoi de %d entiers\n", size);
            MPI_Send(dummyBuffer, size, MPI_INT, 1, 0,
                        MPI_COMM_WORLD);
            MPI_Recv(dummyBuffer, size, MPI_INT, 1, 0,
                        MPI_COMM_WORLD, &status);
        }
        else {
            MPI_Send(dummyBuffer, size, MPI_INT, 0, 0,
                        MPI_COMM_WORLD);
            MPI_Recv(dummyBuffer, size, MPI_INT, 0, 0,
                        MPI_COMM_WORLD, &status);
        }
        size = size*10;
    }

    if (myRank == 0) {
        printf("Fin des envois\n");
    }

    MPI_Finalize();
}
