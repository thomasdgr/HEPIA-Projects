CC=mpicc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=undefined
LD_FLAGS=-lm

all : clean build

build : src/main.o src/matrix/matrix.o
	@$(CC) $^ -o laplace.out $(CFLAGS) $(CFLAGS_ASAN) $(LD_FLAGS)

main.o : main.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LD_FLAGS)

matrix.o : matrix.c matrix.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LD_FLAGS)

clean :
	@find . -name '*.o' -delete
	@rm -f *.o laplace.out laplace.txt