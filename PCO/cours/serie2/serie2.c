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

/******** EX 1 ********/
void *thread_ex1(void *thread_id){
    int id = *((int *)thread_id);
    printf("Hello from thread %d\n", id);
    return NULL;
}

/******** EX 2 ********/
array arr;
int res = 0;

void *thread_ex2(){
    for(int i = 0; i < arr.length; i++){
        res += arr.data[i];
    }
    return NULL;
}

/******** EX 3 ********/
void* thread_ex3(void* array_in){
    array arr2 = *(array *)array_in;
    int* sum = malloc(1 * sizeof(int));
    *sum = 0;
    for(int i = 0; i < arr2.length; i++){
        *sum += arr2.data[i];
    }
    return (void*)sum;
}

int main(int argc, char* argv[]){
    /******** EX 1 ********/
    pthread_t threads[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++){
        int code = pthread_create(&threads[i], NULL, thread_ex1, &i);
        if(code != 0){
            fprintf(stderr, "pthread_create failed!\n");
            return EXIT_FAILURE;
        }
        code = pthread_join(threads[i], NULL);
        if (code != 0){
            fprintf(stderr, "pthread_join failed!\n");
            return EXIT_FAILURE;
        }
    }
    printf("\n");

    /******** EX 2 ********/
    arr.data = malloc(10 * sizeof(int));
    arr.length = argc;
    for(int i = 0; i < arr.length; i++){
        arr.data[i] = atoi(argv[i]);
    }
    pthread_t t;
    int code = pthread_create(&t, NULL, thread_ex2, NULL);
    if(code != 0){
        fprintf(stderr, "pthread_create failed!\n");
        return EXIT_FAILURE;
    }
    code = pthread_join(t, NULL);
    if (code != 0){
        fprintf(stderr, "pthread_join failed!\n");
        return EXIT_FAILURE;
    }
    printf("ex2, somme = %d\n\n",res);

    /******** EX 3 ********/
    int* sum;
    code = pthread_create(&t, NULL, thread_ex3, (void*)&arr);
    if(code != 0){
        fprintf(stderr, "pthread_create failed!\n");
        return EXIT_FAILURE;
    }
    code = pthread_join(t, (void**)&sum);
    if (code != 0){
        fprintf(stderr, "pthread_join failed!\n");
        return EXIT_FAILURE;
    }
    printf("ex3, somme = %d\n",*sum);
    free(sum);

    

    return EXIT_SUCCESS;
}