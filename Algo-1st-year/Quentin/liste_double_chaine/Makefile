all:chaine_double_main.o chaine_double_part.o
		gcc chaine_double_main.o chaine_double_part.o -o main
chaine_double_main.o: chaine_double_main.c
		gcc -c chaine_double_main.c
chaine_double_part.o: chaine_double_part.c
		gcc -c chaine_double_part.c
clean:
	rm *.o
