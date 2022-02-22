#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct barrier_t{
	pthread_mutex_t mutex;
	int max;
	int crt;
} barrier_t;

void barrier_init(barrier_t *b, int count){
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	pthread_mutex_init(&b->mutex, &attr);
	b->max = count;
	b->crt = 0;
}

void barrier_wait(barrier_t *b){
	pthread_mutex_lock(&b->mutex);
	b->crt ++;
	pthread_mutex_unlock(&b->mutex);
	while(b->crt < b->max){}
}

void barrier_destroy(barrier_t *b){
	pthread_mutex_destroy(&b->mutex);
	b->crt = 0;
	b->max = 0;
}

barrier_t kek;

void* func(){
	printf("2nd thread before barrier\n");
	barrier_wait(&kek);
	printf("2nd thread after barrier \n");
}

int main(){
	printf("main thread started\n");
	barrier_init(&kek, 2);
	
	pthread_t thread;
	pthread_create(&thread, NULL, func, NULL);
	
	barrier_wait(&kek);	
	printf("main thread finished\n");
	pthread_join(thread, NULL);
	
	barrier_destroy(&kek);
	return EXIT_SUCCESS;
}