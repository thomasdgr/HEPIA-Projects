CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g -std=c11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: main

main: main.o quadtree.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN) $(LDFLAGS)
	./main

quadtree.o: quadtree.c quadtree.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean:
	find . -name '*.o' -delete
	rm -f *.o main
