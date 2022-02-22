#include <mpi.h>
#include <stdio.h>

/*  MPI_Send(
        void* data,
        int count,  // nombre d'éléments qui composent data
        MPI_Datatype datatype,  // le type de data
        int destination, // thread de destination
        int tag,  // le tag doit etre le même entre send() et recv()
        MPI_Comm communicator  // à laisser tel quel
    )

    MPI_Recv(void* data, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm communicator, MPI_Status* status)
*/

int main(int argc, char **argv) {
    int myRank;
    int nProc;

    int k = 4;
    int nb;
    
    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
    // vérifie qu'on ne lance qu'avec 2 threads le programme ou alors on quitte
    if(nProc > 2){
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    for(int i = 0; i < k; i++){
        if(myRank == 0){
            nb = 420;
            MPI_Send(&nb, 1, MPI_INT, 1, 69, MPI_COMM_WORLD);   
        } else if(myRank == 1){
            MPI_Status status;
            MPI_Recv(&nb, 1, MPI_INT, 0, 69, MPI_COMM_WORLD, &status);
            printf("Process 1 received number %d from process 0\n", nb);
        }
    }
    
    MPI_Finalize(); // termine correctement les threads
}
