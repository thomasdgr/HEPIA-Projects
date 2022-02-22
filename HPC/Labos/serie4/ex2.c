#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    int myRank;
    int nProc;
    const int size = 1000000;

    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);

    // rajouté pour le i send et i receive()
    MPI_Request send_request, recv_request;
    
    const int voisin_gauche = (myRank+nProc-1) % nProc;
    const int voisin_droite = (myRank+1) % nProc;

    int* bufSend = malloc(size*sizeof(int));
    int* bufRecv = malloc(size*sizeof(int));

    bufSend[0] = myRank;

    for (int iEnvoi = 0; iEnvoi < nProc; ++iEnvoi) {
        // le send est à remplacer par un Isend (envoi non-bloquant). Pour cela on a besoin d'une MPI_Request
        //MPI_Send(&bufSend[0], size, MPI_INT, voisin_droite, 0, MPI_COMM_WORLD); 
        MPI_Isend(&bufSend[0], size, MPI_INT, voisin_droite, 0, MPI_COMM_WORLD, &send_request);

        MPI_Irecv(&bufRecv[0], size, MPI_INT, voisin_gauche, 0, MPI_COMM_WORLD, &recv_request);
        
        MPI_Wait(&send_request, &status);
        MPI_Wait(&recv_request, &status);
    
        bufSend[0] = bufRecv[0];
        if (myRank == 0) {
            printf("Le message actuel est %d\n", bufRecv[0]);
        }
    }
    MPI_Finalize();
}