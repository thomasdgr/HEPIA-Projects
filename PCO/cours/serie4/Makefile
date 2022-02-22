CC=gcc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: clean main

main : serie4.o
	@$(CC) $^ -o main $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

serie4.o : serie4.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)
	
clean: 
	@find . -name '*.o' -delete
	@rm -f *.o *.vec main
