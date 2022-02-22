#include "multithreading_utilities.h"
/* create a mutex
 * arg: void
 * return: a pointer on the new mutex
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
 * arg: a pointer on the mutex to lock
 * return: void
 */
void mutex_lock(pthread_mutex_t *mutex) {
    int status = pthread_mutex_lock(mutex);
    if (status){
        fprintf(stderr, "Failed to lock mutex\n");	
        exit(EXIT_FAILURE);
    }
}

/* unlock a mutex
 * arg: a pointer on the mutex to unlock
 * return: void
 */
void mutex_unlock(pthread_mutex_t *mutex) {
    int status = pthread_mutex_unlock(mutex);
    if (status){
        fprintf(stderr, "Failed to unlock mutex\n");	
        exit(EXIT_FAILURE);
    }
}

/* destroy a mutex
 * arg: a pointer on the mutex to destroy
 * return: void
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
 * arg: a pointer on the pthread to create
 * 	  a pointer on the start_routine to use
 *	  the arg used in the start_routine
 * return: void
 */
void thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg) {
    int status = pthread_create(thread, NULL, start_routine, arg);
    if (status){
        fprintf(stderr, "Failed to create thread\n");	
        exit(EXIT_FAILURE);
    }
}

/* join a thread
 * arg: a pthread to join
 *	  the value where we store data from the thread
 * return: void
 */
void thread_join(pthread_t thread, void **retval) {
    int status = pthread_join(thread, retval);
    if (status){
        fprintf(stderr, "Failed to join thread\n");	
        exit(EXIT_FAILURE);
    }
}

/* create a semaphore
 * count: initial counter of the semaphore
 * return: a semaphore
 */
sem_t *sema_create(int count) {
	sem_t *sem = malloc(sizeof(sem_t));
	if (!sem){
		fprintf(stderr, "Malloc failed on sem\n");	
        exit(EXIT_FAILURE);
	} 
	int status = sem_init(sem, 0, count);
	if (status){
        fprintf(stderr, "Failed to create sem\n");	
        exit(EXIT_FAILURE);
    }
	return sem;
}

/* post on a semaphore
 * sem: semaphore to post
 * return: void
 */
void sema_post(sem_t *sem) {
	int status = sem_post(sem);
	if (status){
        fprintf(stderr, "Failed on sem post\n");	
        exit(EXIT_FAILURE);
    }
}

/* wait on a semaphore
 * sem: semaphore to wait
 * return: void
 */
void sema_wait(sem_t *sem) {
	int status = sem_wait(sem);
	if (status){
        fprintf(stderr, "Wait failed on sem\n");	
        exit(EXIT_FAILURE);
    }
}

/* free a semaphore
 * sem: semaphore to destroy
 * return: void
 */
void sema_destroy(sem_t *sem) {
	int status = sem_destroy(sem);
	if (status){
        fprintf(stderr, "Failed to destroy sem\n");	
        exit(EXIT_FAILURE);
    }
	free(sem);
}

/* create a barrier made of a semaphore
 * b: barrier to init
 * count: number of threads to synchronize
 * return: void
 */
void sem_barrier_init(sem_barrier *b, int count) {
	b->count = count;
	b->initialValue = count;
	b->lock = mutex_create();
	b->sem = sema_create(0);
}

/* wait on a barrier 
 * b: barrier to wait
 * return: void
 */
void sem_barrier_wait(sem_barrier *b) {
	mutex_lock(b->lock);
	b->count--;
	if (b->count == 0){
		sema_post(b->sem);
	}
	mutex_unlock(b->lock);

	sema_wait(b->sem);

	mutex_lock(b->lock);
	b->count++;
    if(b->count < b->initialValue){
		sema_post(b->sem);
	}
	mutex_unlock(b->lock);
}

/* destroy a barrier 
 * b: barrier to free
 * return: void
 */
void sem_barrier_destroy(sem_barrier *b) {
	mutex_destroy(b->lock);
	sema_destroy(b->sem);
}