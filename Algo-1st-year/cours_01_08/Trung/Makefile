CC=gcc
CFLAGS=-Wall -Wextra -g -std=c11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: run

run: main.o bin_tree.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN)

bin_tree.o: bin_tree.c bin_tree.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

main.o: main.c bin_tree.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean:
	rm -f *.o run

.PHONY: clean test
