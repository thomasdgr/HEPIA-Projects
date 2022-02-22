#include <error.h>
#include <errno.h>
#include <stdlib.h>
#include "thread_wrapper.h"

#define ERR_CODE 1

pthread_mutex_t *mutex_create() {
	pthread_mutex_t *mutex = malloc(sizeof(pthread_mutex_t));
	if (!mutex) error(ERR_CODE, ENOMEM, "malloc failed!");
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
	int status = pthread_mutex_init(mutex, &attr);
	if (status) error(ERR_CODE, status, "pthread_mutex_init failed!");
	pthread_mutexattr_destroy(&attr);
	return mutex;
}

void mutex_lock(pthread_mutex_t *mutex) {
	int status = pthread_mutex_lock(mutex);
	if (status) error(ERR_CODE, status, "pthread_mutex_lock failed!");
}

void mutex_unlock(pthread_mutex_t *mutex) {
	int status = pthread_mutex_unlock(mutex);
	if (status) error(ERR_CODE, status, "pthread_mutex_unlock failed!");
}

void mutex_destroy(pthread_mutex_t *mutex) {
	int status = pthread_mutex_destroy(mutex);
	if (status) error(ERR_CODE, status, "pthread_mutex_destroy failed!");
	free(mutex);
}

pthread_barrier_t *bar_create(int count) {
	pthread_barrier_t *b = malloc(sizeof(pthread_barrier_t));
	int status = pthread_barrier_init(b, NULL, count);
	if (status) error(ERR_CODE, status, "pthread_barrier_init failed!");
	return b;
}

void bar_destroy(pthread_barrier_t *b) {
	int status = pthread_barrier_destroy(b);
	if (status) error(ERR_CODE, status, "pthread_barrier_destroy failed!");
	free(b);
}

void bar_wait(pthread_barrier_t *b) {
	int status = pthread_barrier_wait(b);
	if (status != PTHREAD_BARRIER_SERIAL_THREAD && status != 0) error(ERR_CODE, status, "pthread_barrier_wait failed!");
}

void thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg) {
	int status = pthread_create(thread, NULL, start_routine, arg);
	if (status) error(ERR_CODE, status, "pthread_create failed!");
}

void thread_join(pthread_t thread, void **retval) {
	int status = pthread_join(thread, retval);
	if (status) error(ERR_CODE, status, "pthread_join failed!");
}

