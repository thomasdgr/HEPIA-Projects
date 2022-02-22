#include "matrix/matrix.h"
#include <time.h>

int main(int argc, char* argv[]){
    int rank;
    int nProc;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    matrix U;
    int t = 0;
    if(argc == 4){
        U = init_tab(atoi(argv[1]), atoi(argv[2]));
        t = atoi(argv[3]);
    } else if(argc == 3){
        U = read_file(argv[1]);
        t = atoi(argv[2]);
    } else {
        printf("argument error\n");
        MPI_Finalize();
        return 1;
    }
    int* nbLines = compute_lines(U.m, U.n, nProc);
    matrix myData = init_tab(nbLines[rank]/U.n, U.n);
    int* displacement = compute_displacement(rank, nProc, nbLines, U.n);
    if(nProc > 1){
        MPI_Scatterv(&(U.data[0][0]), nbLines, displacement, MPI_DOUBLE, &(myData.data[0][0]), nbLines[rank], MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    const int voisin_gauche = (rank+nProc-1) % nProc;
    const int voisin_droite = (rank+1) % nProc;
    for(int i = 0; i < t; i++){
        if(rank == 0 && nProc > 1){ // première ligne
            double* bufRecv = get_missing_line(myData, myData.m - 2, voisin_droite, voisin_droite, 0, 1); 
            apply_laplace(&myData, bufRecv, NULL);
            free(bufRecv);
        }else if(rank == (nProc-1) && nProc > 1){ // dernière ligne
            double* bufRecv = get_missing_line(myData, 1, voisin_gauche, voisin_gauche, 1, 0); 
            apply_laplace(&myData, NULL, bufRecv);
            free(bufRecv);
        }else if(nProc > 1){ // autres lignes
            double* bufRecv1 = get_missing_line(myData, myData.m -2, voisin_droite, voisin_droite, 0, 1);      
            double* bufRecv2 = get_missing_line(myData, 1, voisin_gauche, voisin_gauche, 1, 0); 
            apply_laplace(&myData, bufRecv1, bufRecv2);
            free(bufRecv1);
            free(bufRecv2);
        }else{
            apply_laplace(&U, NULL, NULL);
        }
    }
    if(nProc > 1){
        update_lines(nbLines, nProc, U.n);
        update_displacement(displacement, nbLines, nProc, rank);
        MPI_Gatherv(&(myData.data[(rank != 0)][0]), nbLines[rank], MPI_DOUBLE, &(U.data[0][0]), nbLines, displacement, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    }
    if(rank == 0){
        write_file("laplace.txt", U);
    }
    free_tab(&U);
    free_tab(&myData);
    free(nbLines);
    free(displacement);
    MPI_Finalize();
    return 0;
}