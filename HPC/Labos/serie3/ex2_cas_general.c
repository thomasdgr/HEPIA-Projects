#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Faut faire des prints partout pour savoir ou ca plante

int main(int argc, char *argv[]){
    int rank;
    int nProc;
    MPI_Init(&argc, &argv); // initialise les threads
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // donne le rang du thread actuel
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);  // nombre de processus souhaités
    
    MPI_Status status;
    double starttime, endtime;
    starttime = MPI_Wtime();
    
    srand(time(NULL));
    int n = atoi(argv[1]);

    //printf("p%d:\n",rank);
    // tableau des notes communes (seul p0 le remplie et va l'envoie -> voir l'avant dernier apramètre de scatterv)
    int * notes = malloc(n*sizeof(int));
    if(rank == 0){
        //printf("  all notes: ");
        for(int i = 0; i < n; i++){
            notes[i] = (rand() % 6) + 1;
            //printf("%d - ", notes[i]);
        }
        //printf("\n");
    }

    // chaque p* a, a peu près le même nombre de notes on doit donc connaitre la taille
    int *nbNotes = calloc(0, nProc*sizeof(int));
    for(int i = 0; i < nProc; i++){
        int nb = n / nProc;
        if( n % nProc > i){
            nb++;
        }
        nbNotes[i] = nb;
    }

    
    //printf("  got %d/%d notes\n", nbNotes[rank], n);
    // création du tableau des notes propres à chaque p*
    int *myNotes = malloc(nbNotes[rank]*sizeof(int));

    // création du tableau de displacement (qui doit le créer ce tableau ?)
    int * displacement = malloc(nProc*sizeof(int));
    if(rank == 0){
        for(int i = 0; i < nProc; i++){
            if (i == 0) {
                displacement[i] = 0;
            } else {
                displacement[i] = displacement[i-1] + nbNotes[i-1];
            }
        }
    }

    MPI_Scatterv(notes, nbNotes, displacement, MPI_INT, myNotes, nbNotes[rank], MPI_INT, 0, MPI_COMM_WORLD);

    int sum = 0;
    for(int i = 0; i < nbNotes[rank]; i++){
        sum += myNotes[i];
    }

    int* allSums;
    if (rank == 0){
        allSums = malloc(nProc*sizeof(int));
    }
    MPI_Gather(&sum, 1, MPI_INT, allSums, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if(rank == 0){
        int totSum = 0;
        for (int i = 0; i < nProc; i++) {
            totSum += allSums[i];
        }
        //printf("moyenne=%f\n", (double)totSum / (double)n);
        endtime = MPI_Wtime();
        printf("N=%d\nP=%d\nTime=%f\n", 0 ,nProc, endtime-starttime);
    }
    
    free(notes);
    free(nbNotes);
    free(myNotes);
    free(displacement);
    if(rank == 0){
        free(allSums);
    }

    MPI_Finalize();
    return 0;
}
