#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <limits.h>

int* generateIdentity(unsigned int n) {
    int* I = (int*) malloc(n*n*sizeof(int));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            size_t k = i*n+j;
            if (i == j) {
                I[k] = 1;
            } else {
                I[k] = 0;
            }
        }
    }
    return I;
}

int* generateOneToNN(unsigned int n) {
    int* M = (int*) malloc(n*n*sizeof(int));
    for (size_t k = 0; k < n*n; k++) {
        M[k] = k;
    }
    return M;
}

// implementation de la multiplication 
// matrice-matrice carrée.
int* matMatMult(int* A, int* B, const unsigned int n) {
    int* C = (int*) malloc(n*n*sizeof(int));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {  
            size_t l = i*n + j;
            C[l] = 0;
            for (size_t k = 0; k < n; k++) {
                C[l] += A[i*n+k]*B[k*n+j];
            }
        }
    }
    return C;
}

int main(int argc, char* argv[]) {  
    double starttime, endtime;
    starttime = MPI_Wtime();

    const unsigned int M = atoi(argv[1]);
    const unsigned int n = 16;

    MPI_Init(&argc, &argv);
  
    int myRank;
    int nProc;

  
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProc);
    MPI_Status status;
  
    // yup, we may floor it and we don't care
    int n_tasks = n/nProc; 
  
    //printf("Matrix size is: [%ix%i]\n", M, M);
    //printf("Local number of MM to do: %i\n", n_tasks);
  
    int* A;
    int* B;
    int* C;
  
    for (size_t i = 0; i < n_tasks; i++) {   
        A = generateIdentity(M);
        B = generateOneToNN(M);
        C = matMatMult(A, B, M);
    }
  
    free(A);
    free(B);
    free(C);
   
    MPI_Barrier(MPI_COMM_WORLD);

    endtime = MPI_Wtime();
    if(myRank == 0){
        printf("N=%d\nP=%d\n",M,nProc);
        printf("Time=%f\n",endtime-starttime);
    }

    MPI_Finalize();
    return 0;
}