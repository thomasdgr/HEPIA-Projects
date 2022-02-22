all: queue_array.o main.o
		gcc queue_array.o main.o -o main
queue_array.o: queue_array.c
		gcc -c queue_array.c
main.o: main.c
		gcc -c main.c
clean:
	rm *.o
