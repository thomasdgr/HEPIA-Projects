CC=gcc
CFLAGS=-std=gnu11
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-pthread -lrt -lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: clean main

main : src/main.o src/barrier.o
	@$(CC) $^ -o main $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

main.o : src/main.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

barrier.o : src/barrier.c src/barrier.h 
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

clean: 
	@find . -name '*.o' -delete
	@rm -f *.o main 