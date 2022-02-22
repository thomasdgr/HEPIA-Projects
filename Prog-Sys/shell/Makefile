CC=gcc
COMPILE_OPTS= -Wall -Wextra -g -std=gnu11
OPTIM_OPTS= -O3
SANITIZERS= -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
LIBS=-lm

all: clean main

main: src/main.o src/parsing.o src/jobs.o src/builtin.o
	$(CC) $^ -o $@ $(LIBS) $(SANITIZERS) $(OPTIM_OPTS)

%.o : %.c
	$(CC) $(COMPILE_OPTS) $(OPTIM_OPTS) $(SANITIZERS) -c $^ -o $@

clean:
	rm -f src/*.o
	rm -f main
