include ../../common.mk

all: error.o

error.o: error.c error.h
	@$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean: 
	@rm -f *.o

