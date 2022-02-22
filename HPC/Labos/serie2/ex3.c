#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
    int rank;
    int p;
    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &p);  // nombre de processus souhaités
    
    int n = p * 2;
    int m = n/p;

    int* v = malloc(m*sizeof(int));
    int val = rank;
    int recep = 0;
    int nb_etapes = log2(p);

    MPI_Status status;

    for(int i = 0; i < nb_etapes; i++){

        int first_process_at_step_n = (int) pow(2, i) - 1;
        int gap_between_process_at_step_n = (int) pow(2, i+1);
        
        if((rank - first_process_at_step_n) % gap_between_process_at_step_n == 0){
            printf("Process %d send number %d to process %d\n", rank, val, rank + (int)pow(2, i));
            MPI_Send(&val, 1, MPI_INT, rank + (int)pow(2, i), 666, MPI_COMM_WORLD);
            break;
        }
        MPI_Recv(&recep, 1, MPI_INT, rank - (int)pow(2, i), 666, MPI_COMM_WORLD, &status);
        val += recep;
    }

    if(rank == p -1){
        printf("result=%d\n", val);
    }
    MPI_Finalize(); // termine correctement les threads
}
