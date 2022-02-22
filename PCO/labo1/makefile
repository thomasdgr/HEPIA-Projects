CC=gcc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-lm -lrt
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: clean main

main : src/convolve/convolve.o src/ppm/ppm.o src/main.o
	@$(CC) $^ -o main $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

main.o : src/main.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

convolve.o : convolve.c convolve.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

ppm.o : ppm.c ppm.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

clean:
	@find . -name '*.o' -delete
	@rm -f *.o main
