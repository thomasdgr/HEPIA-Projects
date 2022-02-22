include ./common.mk

# Makefile fait l'année dernière au libre service
# avec l'aimable participation de Michaël El Kharroubi

# emplacement des autres fichiers à compiler + Makefiles
SUB_DIRS= ./src/error ./src/options
.PHONY: sub_dirs clean test

# recherche des dépendances se trouvant dans le dossier src/
O_DEPS=$(shell find $(shell pwd)/src/ -name "*.o" | tr "\n" " ")
export

all: ultra-cp

# génération de l'éxécutable ultra-cp à partir de tous les fichiers objets
# les flags de compilation se trouvent dans le fichier common.mk
ultra-cp: main.o sub_dirs
	@$(CC) $(CFLAGS) $(CFLAGS_ASAN) $(O_DEPS) main.o $(LDFLAGS) $(LDFLAGS_ASAN) -o $@

# génération du fichier objet main
main.o: src/main.c
	@$(CC) -c $< $(CFLAGS) $(CFLAGS_ASAN)

# appel vers les Makefiles se trouvant dans les dossiers de SUB_DIRS
sub_dirs:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) --no-print-directory -C $$dir; \
	done

clean:
	@rm -f src/*.o ultra-cp main.o
	@for dir in $(SUB_DIRS); do \
		$(MAKE) clean --no-print-directory -C $$dir; \
	done