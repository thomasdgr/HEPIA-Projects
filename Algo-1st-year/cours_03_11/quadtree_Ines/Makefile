CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g -std=c11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer

main: quadtree.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN)

%.o: %.c 
	$(CC) $(CFLAGS) $(CFLAGS_ASAN) -c $^ -o $@

clean:
	rm -f *.o main