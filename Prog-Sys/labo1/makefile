CC=gcc
CFLAGS=-std=gnu11 -g -O3 -Wall -Wextra -pedantic
CFLAGS_ASAN=-fno-omit-frame-pointer -fsanitize=address -fsanitize=undefined -fsanitize=leak
LDFLAGS=-lm -lrt
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

all: clean shell

shell: src/main.o src/command/command.o src/color/color.o src/tools/tools.o src/jobs/jobs.o
	@$(CC) $^ -o shell $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

main.o: src/main.c
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

command.o: command.c command.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

color.o: color.c color.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

tools.o: tools.c tools.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

jobs.o: jobs.c jobs.h
	@$(CC) $^ -c $< $(CFLAGS) $(CFLAGS_ASAN) $(LDFLAGS)

clean:
	@find . -name '*.o' -delete
	@rm -f *.o shell
