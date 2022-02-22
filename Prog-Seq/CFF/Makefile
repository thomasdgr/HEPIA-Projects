CC=gcc
CFLAGS=-Wall -Wextra -pedantic -g -std=gnu11 -O3
CFLAGS_ASAN=-fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lm
LDFLAGS_ASAN=-fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer

all: clean main

main: src/xml_parser/xml_parser.o src/main.o src/error/error.o src/priority_queue/priority_queue.o src/heapsort/heapsort.o src/priority_queue/priority_queue_generic.o src/vector_list/city_list.o src/vector_list/connection_list.o src/matrix/matrix.o src/dijkstra_floyd/dijkstra.o
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN) $(LDFLAGS) -I/usr/include/libxml2 -lxml2

src/main.o: src/main.c 
	@$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN) $(LDFLAGS) -I/usr/include/libxml2
	
src/xml_parser/xml_parser.o: src/xml_parser/xml_parser.c src/xml_parser/xml_parser.h
	@$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN) $(LDFLAGS) -I/usr/include/libxml2

test: src/error/error.o src/priority_queue/priority_queue.o src/heapsort/heapsort.o src/priority_queue/priority_queue_generic.o src/vector_list/city_list.o src/vector_list/connection_list.o src/matrix/matrix.o src/dijkstra_floyd/dijkstra.o src/test/test.o src/test/test_priority_queue.o src/test/test_heapsort.o src/test/test_list.o src/test/test_matrix.o
	@$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(LDFLAGS_ASAN) $(LDFLAGS) -lcunit
	@./test

clean:
	@find . -name '*.o' -delete
	@rm -f *.o *.gch test main