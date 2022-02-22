CC=gcc
CFLAGS=-Wall -Wextra -g -std=c11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: run

run: main.o chaine_double.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN)

chaine_double.o: chaine_double.c chaine_double.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

main.o: main.c chaine_double.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)


clean:
	rm -f *.o run

.PHONY: clean run
