GCC=gcc -O2 -Wall -std=gnu99 -g
LIBS=-lSDL2 -lSDL2_image -lpthread

BIN=one_armed_bandit
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
HEADERS=$(wildcard *.h)

$(BIN): $(OBJS)
	$(GCC) $^ -o $@ $(LIBS)

run: $(BIN)
	./$< 

%.o: %.c $(HEADERS)
	$(GCC) $< -c

clean:
	rm -f $(BIN) $(OBJS)