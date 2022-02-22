/*****************************************************************************
		     ____
           /____ \         | Projet : TP sur l'utilisation des barrières et des
           | _ _`\|        |          mutex dans le cadre du cours de PCO
    .-.   `| O O |         | Auteurs : Quentin ROD, Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Code permettant de manipuler des
(___)  )\/  \_____/  ~\.   |                mutexs (repris du fichier fournis
(___) . \   `         `\   |                dans l'énnoncé de l'exercice 2)
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 21/04/2021

*****************************************************************************/

#include "barrier.h"

/* create a mutex
 arg: void
 return: a pointer on the new mutex
*/
pthread_mutex_t* mutex_create(){
    pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
    if (!mutex){
        fprintf(stderr, "Failed to malloc mutex\n");	
        exit(EXIT_FAILURE);
    }
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    if(pthread_mutex_init(mutex, &attr)){
        fprintf(stderr, "Failed to init mutex\n");	
        exit(EXIT_FAILURE);
    }
    pthread_mutexattr_destroy(&attr);
    return mutex;
}

/* lock a mutex
 arg: a pointer on the mutex to lock
 return: void
*/
void mutex_lock(pthread_mutex_t *mutex) {
    int status = pthread_mutex_lock(mutex);
    if (status){
        fprintf(stderr, "Failed to lock mutex\n");	
        exit(EXIT_FAILURE);
    }
}

/* unlock a mutex
 arg: a pointer on the mutex to unlock
 return: void
*/
void mutex_unlock(pthread_mutex_t *mutex) {
    int status = pthread_mutex_unlock(mutex);
    if (status){
        fprintf(stderr, "Failed to unlock mutex\n");	
        exit(EXIT_FAILURE);
    }
}

/* destroy a mutex
 arg: a pointer on the mutex to destroy
 return: void
*/
void mutex_destroy(pthread_mutex_t *mutex) {
    int status = pthread_mutex_destroy(mutex);
    if (status){
        fprintf(stderr, "Failed to destroy mutex\n");	
        exit(EXIT_FAILURE);
    }
    free(mutex);
}

/* create a thread
 arg: a pointer on the pthread to create
	  a pointer on the start_routine to use
	  the arg used in the start_routine
 return: void
*/
void thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg) {
    int status = pthread_create(thread, NULL, start_routine, arg);
    if (status){
        fprintf(stderr, "Failed to create thread\n");	
        exit(EXIT_FAILURE);
    }
}

/* join a thread
 arg: a pthread to join
	  the value where we store data from the thread
 return: void
*/
void thread_join(pthread_t thread, void **retval) {
    int status = pthread_join(thread, retval);
    if (status){
        fprintf(stderr, "Failed to join thread\n");	
        exit(EXIT_FAILURE);
    }
}
