CC=gcc
CFLAGS=-g
LDFLAGS=-lm

.PHONY: all clean

all: server client

server: server.o common.o
	$(CC) server.o common.o -o server

client: client.o common.o
	$(CC) client.o common.o -o client $(LDFLAGS)

server.o: server.c common.o
	$(CC) $(CFLAGS) -c server.c -o server.o

client.o: client.c common.o
	$(CC) $(CFLAGS) -c client.c -o client.o

common.o: common.c common.h
	$(CC) $(CFLAGS) -c common.c -o common.o

clean:
	rm *.o server client