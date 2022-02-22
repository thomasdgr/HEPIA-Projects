include ../../common.mk

all: options.o

options.o: options.c options.h
	@$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean: 
	@rm -f *.o
