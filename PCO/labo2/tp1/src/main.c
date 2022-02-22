/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur l'utilisation des barrières et des
           | _ _`\|        |          mutex dans le cadre du cours de PCO
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Utiliser la concurence pour calculer
(___)  )\/  \_____/  ~\.   |                une somme de termes à l'aide de
(___) . \   `         `\   |                barrières
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 21/04/2021

*****************************************************************************/
#include <time.h>
#include <sys/time.h>
#include <math.h>

#include "barrier.h"

// const used for the sum (doesn't need to be changed)
int A = 100;

// inputs of the program
int M,   // the number of sin in each sum
    N;   // the number of thread used to calculate each sum
        //Also, I the number of sum to calculate through the hole program

// values are stored in a 2D vector (2 arrays used to read OR write)
double* tabPartA1;
double* tabPartA2;

double totalRes = 0;
pthread_barrier_t barrierRk;
pthread_barrier_t barrierRk2;
struct timespec start, finish;
pthread_mutex_t* mutexPartA;
pthread_mutex_t* mutexPartA2;
pthread_mutex_t* mutexPartA3;

/* sum used to compare the sequential method with the multi-threaded one
 arg: k, constant
      M, the number of args to calculate for the sum
      A, constant
 return: the result of the sum
*/
double sum(int k, int M, int A){
    double resSum = 0;
    for(int i = 0; i < M; i++){
        double resSinus = sin(k + i);
        if(resSinus > 0){
            resSum += A * resSinus;
        }
    }
    return resSum;
}

void sequentialMethod(int I){
    printf("\nsequential method:\n");
    // start the timer here
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0){
        exit(EXIT_FAILURE);
    }
    for (int k = 0; k < I; k++){
        printf("r(%d)=%lf\n",k, sum(k, M, A));
    }
    // stop the timer here
    if(clock_gettime(CLOCK_MONOTONIC, &finish) != 0){
        exit(EXIT_FAILURE);
    }

    double elapsed_ms = 1000 * (finish.tv_sec - start.tv_sec);
    elapsed_ms += (finish.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("time elapsed for sequential method: %.4fms\n", elapsed_ms);
}

/* function that calculate all the sin() we want to sum on threadPartB()
 arg: arg, a void*, casted to a partialSum
 return: void
*/
int finished_count = 0;
void* threadPartA(void* arg){
    // flip is used to make sure we write and we read on differents tabs form the 2D vector
    static int countCalcul = 0;
    partialSum *pS = (partialSum *)arg;
    // we make sure all thread are doing the same amount of job
    int finished = 0;
    int i = 0;
    while(1){
        if(i>=M){
          mutex_lock(mutexPartA3);
          if(finished_count == pS->numberOfThreadsPartA){
            mutex_unlock(mutexPartA3);
            break;
          }
          mutex_unlock(mutexPartA2);
        }
        double resSinus = A * sin(pS->k + i);
        if(resSinus > 0){
            tabPartA1[pS->idThread] = resSinus;
        }else{
            tabPartA1[pS->idThread] = 0;
        }

        mutex_lock(pS->mutex); //Protect access to shared variable countCalcul
        countCalcul++;
        mutex_unlock(pS->mutex);
        // we change the arrays on which we write and read only if this is the last thread that is going through this loop
        if(countCalcul == pS->numberOfThreadsPartA ){
            countCalcul = 0;
            double *tabPartATmp = tabPartA1;
            tabPartA1 = tabPartA2;
            tabPartA2 = tabPartATmp;
        }

        i += pS->numberOfThreadsPartA;
        if(i >= M){
            mutex_lock(mutexPartA2);
            ++finished_count;
            mutex_unlock(mutexPartA2);
        }

        pthread_barrier_wait(&barrierRk);
        pthread_barrier_wait(&barrierRk2);
    }

}

/* function that calculate the sum for every sin() calculated on threadPartB()
 arg: arg, a void*, casted to a partialSum
 return: void
*/
void* threadPartB(void* arg){
    static int numberOfCalculsDoneB = 0;
    int numberOfThreadsPartA = *(int *)arg;

    while(numberOfCalculsDoneB < M ){
        pthread_barrier_wait(&barrierRk);
        for (int i = 0; i < numberOfThreadsPartA; i++){
            totalRes += tabPartA2[i];
            numberOfCalculsDoneB++;
        }
        pthread_barrier_wait(&barrierRk2);

    }
    numberOfCalculsDoneB = 0;
}

// marche pour n'importe quel M
// problème quand N > 3
// marche pour n'importe quel I

int main(int argc, char **argv) {
    if (argc != 4 || atoi(argv[3]) == 0 || atoi(argv[2]) == 0 || atoi(argv[1]) == 0) {
        fprintf(stderr, "usage: %s <M> <N> <I>\n"\
        "where M,N,I are u_int values\n", argv[0]);
         return EXIT_FAILURE;
    }

    M = atoi(argv[1]); // the number of sin in each sum
    N = atoi(argv[2]); // the number of thread used to calculate each sum
    int I = atoi(argv[3]); // the number of sum to calculate through the hole program

    // verify the consistency of the inputs
    if(I < 0){
        fprintf(stderr, "\'I\' must be greater than 0\n");
        return EXIT_FAILURE;
    } else if(N <= 1){
        fprintf(stderr, "\'N\' must be greater than 1\n");
        return EXIT_FAILURE;
    } else if(M <= N){
        fprintf(stderr, "\'M\' must be greater than \'N\'\n");
        return EXIT_FAILURE;
    }

    // create pthreads for the threadPartA()
    int numberOfThreadPartA = N - 1; // should always be N - 1
    pthread_t partialCalculThreadA[numberOfThreadPartA];
    tabPartA1 = malloc(sizeof(double) * numberOfThreadPartA);
    tabPartA2 = malloc(sizeof(double) * numberOfThreadPartA);

    // create pthreads for the threadPartB()
    int numberOfThreadPartB = 1; // should always be 1
    pthread_t partialCalculThreadB[numberOfThreadPartB];

    // create the mutex used for each pthread on threadPartA()
    pthread_mutex_t* mutexPartA = mutex_create();
    mutexPartA2 = mutex_create();
    mutexPartA3 = mutex_create();

    // create the barrier used of the two thread functions
    pthread_barrier_init(&barrierRk, NULL, N);
    pthread_barrier_init(&barrierRk2, NULL, N);

    // loop to calculate the sum with the multi-threaded method
    printf("\nmulti-threaded method:\n");
    // start the timer here
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0){
        return EXIT_FAILURE;
    }

    for (int k = 0; k < I; k++){
        // create the threads for part A and B
        for (int i = 0;  i < numberOfThreadPartB; i++){
            thread_create(&partialCalculThreadB[i], threadPartB, &numberOfThreadPartA);
        }

        partialSum pSArray[numberOfThreadPartA];
        for (int i = 0; i < numberOfThreadPartA; i++){
            pSArray[i] = (partialSum){k,numberOfThreadPartA,i,mutexPartA};
            thread_create(&partialCalculThreadA[i], threadPartA, &pSArray[i]);
        }

        // join the threads for part A and B
        for(int i = 0; i< numberOfThreadPartA; i++){
            thread_join( partialCalculThreadA[i], NULL);
        }
        for (int i = 0; i < numberOfThreadPartB; i++){
            thread_join(partialCalculThreadB[i], NULL);
        }
        printf("r(%d)=%lf\n",k, totalRes);
        totalRes = 0;
    }
    // stop the timer here
    if(clock_gettime(CLOCK_MONOTONIC, &finish) != 0){
        return EXIT_FAILURE;
    }

    double elapsed_ms = 1000 * (finish.tv_sec - start.tv_sec);
    elapsed_ms += (finish.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("time elapsed for multi-threaded method: %.4fms\n", elapsed_ms);

    sequentialMethod(I);

    //Free allocated elements
    free(tabPartA1);
    free(tabPartA2);
    pthread_barrier_destroy(&barrierRk);
    pthread_barrier_destroy(&barrierRk2);
    mutex_destroy(mutexPartA);

    return EXIT_SUCCESS;
}
