all: main

main: hachage_part
		gcc main.c hachage_part.o -o main
		./main
hachage_part:
	gcc hachage_part.c -c
clean:
	rm *.o
