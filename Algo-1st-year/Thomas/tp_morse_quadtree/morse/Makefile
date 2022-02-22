CC=gcc
CFLAGS=-Wall -Wextra -g -std=gnu11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: run

run: morse.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN)

morse.o: morse.c
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean:
	rm -f *.o run

.PHONY: clean test
