CC=gcc
CFLAGS=-Wall -Wextra -g -std=c11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: run

run: quadtree.o matrix.o pgm.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN)

matrix.o: matrix.c matrix.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

quadtree.o: quadtree.c
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

pgm.o: pgm.c pgm.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean:
	rm -f *.o run

.PHONY: clean test
