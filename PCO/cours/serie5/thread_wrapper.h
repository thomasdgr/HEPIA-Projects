#ifndef _THREAD_WRAPPER_H_
#define _THREAD_WRAPPER_H_

#include <pthread.h>

extern pthread_mutex_t *mutex_create();
extern void mutex_lock(pthread_mutex_t *mutex);
extern void mutex_unlock(pthread_mutex_t *mutex);
extern void mutex_destroy(pthread_mutex_t *mutex);
extern pthread_barrier_t *bar_create(int count);
extern void bar_destroy(pthread_barrier_t *b);
extern void bar_wait(pthread_barrier_t *b);
extern void thread_create(pthread_t *thread, void *(*start_routine)(void *), void *arg);
extern void thread_join(pthread_t thread, void **retval);

#endif
