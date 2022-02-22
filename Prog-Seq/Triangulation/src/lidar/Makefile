include ../../common.mk

all: lidar.o

lidar.o: lidar.c lidar.h
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

clean: 
	@rm -f *.o
