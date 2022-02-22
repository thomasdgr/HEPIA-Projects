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
    int n = atoi(argv[1]); 
    int nbNotes = n/nProc;
    
    int *notes = malloc(nbNotes*sizeof(int));
    for (int i = 0; i < nbNotes; i++) {
        notes[i] = (rand() % 6) + 1;
    }

    double moyenneLocal = 0.0;
    for (size_t i = 0; i < nbNotes; i+=1) {
        moyenneLocal += notes[i];
    }
    moyenneLocal /= nbNotes;
    
    double moyenneGlobale = 0.0;
    MPI_Reduce(&moyenneLocal, &moyenneGlobale, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        moyenneGlobale /= nProc;
        endtime = MPI_Wtime();
        printf("N=%d\nP=%d\nTime=%f\n", 0 ,nProc, endtime-starttime);
    }

    free(notes);
    MPI_Finalize();
    return 0;
}
