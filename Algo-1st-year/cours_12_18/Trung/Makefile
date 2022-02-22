CC=gcc
CFLAGS=-Wall -Wextra -g -std=c11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: main

main: joseph.o circular_list.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN)

circular_list.o: circular_list.c circular_list.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

joseph.o: joseph.c circular_list.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)


clean:
	rm -f *.o main

.PHONY: clean test
