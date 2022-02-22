#ifndef BARRIER_H
#define BARRIER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <pthread.h>

/* strcut that contains the args used for the partial sum
 contains: k (const)
          numberOfThreadsPartA = the input, N, minus 1 that is used for the thread B
          idThread, the id of the current thread
          mutex, a pointer on a mutex
*/
typedef struct partialSum{
    int k;
    int numberOfThreadsPartA;
    int idThread;
   	pthread_mutex_t* mutex;
} partialSum;

pthread_mutex_t* mutex_create();
void mutex_lock(pthread_mutex_t *mutex);
void mutex_unlock(pthread_mutex_t *mutex);
void mutex_destroy(pthread_mutex_t *mutex);
void thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg);
void thread_join(pthread_t thread, void **retval);
#endif