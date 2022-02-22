#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#include <time.h>
int main(int argc, char *argv[])
{
    //init variables for thread
    int rank;
    int nProc;
    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
    
    MPI_Status status;
    double starttime, endtime;
    starttime = MPI_Wtime();
    
    //init variables appli
    srand(time(NULL));
    int nPadawan = atoi(argv[1]); 
    int *allNote = malloc(nPadawan*sizeof(int));
    int nOperation = nPadawan/nProc;
    
    int *nNoteRecu = malloc(nOperation*sizeof(int));
    double *allMoyenne = malloc(nProc*sizeof(double));

    double moyenne;

    //calcul moyenne
    if(rank==0) {
        for (int i = 0; i < nPadawan; i++) {
            allNote[i] = (rand() % 5) + 1;
        }
    }
    MPI_Scatter(allNote, nOperation, MPI_INT, nNoteRecu, nOperation, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (size_t i = 0; i < nOperation; i++) {
        moyenne += nNoteRecu[i];
    }
    moyenne /= nOperation;
    MPI_Gather(&moyenne, 1, MPI_DOUBLE, allMoyenne, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        double moyenneFinale = 0.0;
        for (size_t i = 0; i < nProc; i++) moyenneFinale += allMoyenne[i];
        moyenneFinale /= nProc;
        endtime = MPI_Wtime();
        printf("N=%d\nP=%d\nTime=%f\n", 0 ,nProc, endtime-starttime);
    }

    free(allNote);
    free(allMoyenne);
    free(nNoteRecu);
    MPI_Finalize();
    return 0;
}
