# Makefile sponsorisé par Michaël

# pour ne pas remplir la console d'informations inutiles
# j'ai placé des @ à certains endroits
include ./common.mk

SUB_DIRS= ./src/vector ./src/geom ./src/lidar ./src/stl ./src/error
.PHONY: sub_dirs clean test

O_DEPS=$(shell find $(shell pwd)/src/ -name "*.o" | tr "\n" " ")
export

main: clean main.o sub_dirs
	@$(CC) $(CFLAGS) $(CFLAGS_ASAN) $(O_DEPS) main.o $(LDFLAGS) $(LDFLAGS_ASAN) -o $@

main.o: src/main.c
	$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

test: clean sub_dirs
	@$(MAKE) --no-print-directory -C src/test

sub_dirs:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) --no-print-directory -C $$dir; \
	done

clean:
	@rm -f src/*.o main main.o
	@for dir in $(SUB_DIRS) src/test; do \
		$(MAKE) clean --no-print-directory -C $$dir; \
	done