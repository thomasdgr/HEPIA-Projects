CC=gcc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: clean main

main : serie3.o
	@$(CC) $^ -o main $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

main.o : serie3.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)
	
clean: 
	@find . -name '*.o' -delete
	@rm -f *.o *.vec main
