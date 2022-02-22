CC=gcc
COMPILE_OPTS= -Wall -Wextra -g -std=gnu11
OPTIM_OPTS= -O3
# il faut lancer docker en mode privileged pour les leak check
SANITIZERS= -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
LIBS=-lcunit -lm -lSDL2

all: clean image_transform compile_test

image_transform: src/image_transform.o src/matrix.o src/pgm.o src/geom.o src/filter.o src/gfx.o
	$(CC) $^ -o $@ $(LIBS) $(SANITIZERS) $(OPTIM_OPTS)

compile_test: src/test/test.o src/test/test_matrix.o src/matrix.o src/test/test_pgm.o src/pgm.o src/test/test_geom.o src/geom.o src/test/test_filter.o src/filter.o
	$(CC) $^ -o test $(LIBS) $(SANITIZERS) $(OPTIM_OPTS)

test: compile_test
	./test

%.o : %.c
	$(CC) $(COMPILE_OPTS) $(OPTIM_OPTS) $(SANITIZERS) -c $^ -o $@

SUBDIR_ROOTS := src
DIRS := . $(shell find $(SUBDIR_ROOTS) -type d)
GARBAGE_PATTERNS := *.o
GARBAGE := $(foreach DIR,$(DIRS),$(addprefix $(DIR)/,$(GARBAGE_PATTERNS)))

clean:
	rm -rf $(GARBAGE)
	rm -f image_transform test

.PHONY: clean test
