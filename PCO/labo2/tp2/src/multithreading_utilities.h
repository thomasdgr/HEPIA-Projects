#ifndef MULTITHREADING_UTILITIES_H
#define MULTITHREADING_UTILITIES_H

#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/* structure used for passive waiting in wheels and interactions threads, 
   but also at the beggining of the display thread
   This semaphore structure is given the the main structure at the beggining of the main()
*/
typedef struct {
	int count;
	int initialValue;
	pthread_mutex_t *lock;
	sem_t *sem;
} sem_barrier;

//Mutex functions
pthread_mutex_t* mutex_create();

void mutex_lock(pthread_mutex_t *mutex);

void mutex_unlock(pthread_mutex_t *mutex);

void mutex_destroy(pthread_mutex_t *mutex);

void thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg);

void thread_join(pthread_t thread, void **retval);

//Semaphore functions
sem_t *sema_create(int count);

void sema_post(sem_t *sem);

void sema_wait(sem_t *sem);

void sema_destroy(sem_t *sem);

//Barrier created with a semaphore
void sem_barrier_init(sem_barrier *b, int count);

void sem_barrier_wait(sem_barrier *b);

void sem_barrier_destroy(sem_barrier *b);

#endif