all: pile.o main.o
		gcc pile.o main.o -o main
pile.o: pile.c
		gcc -c pile.c
main.o: main.c
		gcc -c main.c
clean:
	rm *.o
