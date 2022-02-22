#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "thread_wrapper.h"

#define DEBUG

#define STACK_SIZE 100000
#define THREAD_COUNT 100
#define NB_OF_PUSH_POP 1000

// Barrier used to make sure all threads are created and ready before starting to run the stack test
pthread_barrier_t *b;

typedef struct {
	int max;
    int crt;
    int* data;
  	pthread_mutex_t* mutex;
} stack_t;

typedef struct {
	int id;
	stack_t *stack;
} thr_params;

bool stack_create(stack_t *s, int max_size) {
    if(max_size > 0){
        s->data = malloc(max_size * sizeof(int));
        s->crt = 0;
        s->max = max_size;
        s->mutex = mutex_create();
        return true;
    } else {
        return false;
    }
}

void stack_destroy(stack_t *s) {
	mutex_destroy(s->mutex);
    free(s->data);
}

void stack_push(stack_t *s, int val) {
    mutex_lock(s->mutex);
    if(s->crt < s->max){
        s->data[s->crt] = val;
	    s->crt++;
    }
    mutex_unlock(s->mutex);
}

int stack_pop(stack_t *s) {
    mutex_lock(s->mutex);
    if(s->crt > 0){
	    s->crt--;
    }
    mutex_unlock(s->mutex);
}

bool stack_is_empty(stack_t *s) {
    return s->crt == 0;
}


void *test_stack(void *data) {
	bar_wait(b);

	thr_params *p = (thr_params *)data;
	
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	unsigned int seed = (unsigned int)ts.tv_nsec;

	for (int i = 0; i < NB_OF_PUSH_POP; i++) {
		// push
		int val = rand_r(&seed) % 1000;
		stack_push(p->stack, val);

		// pop
		if (!stack_is_empty(p->stack)) {
			stack_pop(p->stack);
		}
	}
	return NULL;
}

int main() {
	b = bar_create(THREAD_COUNT);

	stack_t s;
	if (!stack_create(&s, STACK_SIZE)) {
		fprintf(stderr, "Failed creating stack!\n");
		return EXIT_FAILURE;
	}
#ifdef DEBUG
	printf("Created stack of %d\n", STACK_SIZE);
#endif

#ifdef DEBUG
	printf("Launching %d threads\n", THREAD_COUNT);
#endif
	pthread_t t[THREAD_COUNT];
	thr_params p[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		p[i].id = i;
		p[i].stack = &s;
		thread_create(&t[i], test_stack, &p[i]);
	}

	for (int i = 0; i < THREAD_COUNT; i++)
		thread_join(t[i], NULL);

#ifdef DEBUG
	printf("Stack empty ? %s\n", stack_is_empty(&s) ? "yes" : "NO!");
#endif

	stack_destroy(&s);
#ifdef DEBUG
	printf("Stack destroyed\n");
#endif

	bar_destroy(b);

	return EXIT_SUCCESS;
}