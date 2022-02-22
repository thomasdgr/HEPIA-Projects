#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 16

typedef struct array {
    int * data;
    int length;
} array;


void* thread(void* array_in){
    array arr2 = *(array *)array_in;
    int* sum = malloc(1 * sizeof(int));
    *sum = 0;
    for(int i = 0; i < arr2.length; i++){
        *sum += arr2.data[i];
    }
    return (void*)sum;
}

int main(int argc, char* argv[]){
    int *sum_int;
    int sum_finale = 0;
    array arr;
    arr.length = atoi(argv[1]);
    arr.data = malloc(arr.length * sizeof(int));
    for(int i = 0; i < arr.length; i++){
        arr.data[i] = i+1;
    }
    
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++){
        int code = pthread_create(&threads[i], NULL, thread, &i);
        if(code != 0){
            fprintf(stderr, "pthread_create failed!\n");
            return EXIT_FAILURE;
        }
        code = pthread_join(threads[i], (void**)&sum_int);
        if (code != 0){
            fprintf(stderr, "pthread_join failed!\n");
            return EXIT_FAILURE;
        }
        sum_finale += *sum_int;
    }
    printf("ex4, somme = %d\n",sum_finale);
    free(sum_int);


    

    return EXIT_SUCCESS;
}