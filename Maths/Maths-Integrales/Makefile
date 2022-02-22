CC=gcc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-lm -lSDL2
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: clean main

main : src/integrales/integrales.o src/arrayPoints/arrayPoints.o src/matrix/matrix.o src/pgm/pgm.o src/vector/vector.o src/gfx/gfx.o src/main.o
	@$(CC) $^ -o main $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

main.o : src/main.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

integrales.o : integrales.c integrales.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

matrix.o : matrix.c matrix.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

pgm.o : pgm.c pgm.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

gfx.o : gfx.c gfx.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

vector.o : vector.c vector.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

arrayPoints.o : arrayPoints.c arrayPoints.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

convolve_s_f : all
	./main f
	python3 src/Python/example.py

convolve_s_h : all
	./main h
	python3 src/Python/example.py

clean:
	@find . -name '*.o' -delete
	@rm -f *.o src/Python/*.vec main
