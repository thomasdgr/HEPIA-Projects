include ../../common.mk

all: stl.o

stl.o: stl.c stl.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

#je vais laisser cette ligne exprès pour Michaël car il dit que sauter des lignes pollue la planete

clean: 
	@rm -f *.o
