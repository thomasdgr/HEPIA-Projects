CC=gcc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: clean main

main : optimisation/optimisation.o main.o vector/vector.o
	@$(CC) $^ -o main $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)
	@./main
	@python3 Python/example.py

main.o : main.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)
	
optimisation.o : optimisation.c optimisation.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

vector.o: vector.c vector.h 
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)


clean: 
	@find . -name '*.o' -delete
	@rm -f *.o *.vec main
