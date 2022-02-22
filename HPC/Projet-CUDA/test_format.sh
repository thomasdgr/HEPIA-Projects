#!/bin/bash
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'
echo_red(){
    echo -e "${RED}$1${NC}"
}
echo_green(){
    echo -e "${GREEN}$1${NC}"
}
clean_tmp()
{
  rm -f test_format.out
}


# Vérifie l'arborescence.
cd src
if [ $? -ne 0 ]; then
    echo_red "L'arborescence de votre projet ne respecte pas l'énoncé"
    clean_tmp
    make clean
    exit 1
fi

# Vérifie que la cible lib respecte l'énoncé.
make clean
make lib
if test ! -f hepia_gpu_lib.o; then
    echo_red "La compilation de la lib ne fonctionne pas"
    cd ..
    clean_tmp
    make clean
    exit 1
fi
cd ..

# Vérifie que le nom des fonctions de la lib respecte l'énoncé.
nvcc test_format.cu src/hepia_gpu_lib.o -o test_format.out
if [ $? -ne 0 ]; then
    echo_red "La compilation du test ne fonctionne pas"
    clean_tmp
    cd src
    make clean
    exit 1
fi

# Vérifie que la lib fonctionne (pas forcèment juste du point de vue des calculs). 
./test_format.out
if [ $? -ne 0 ]; then
    echo_red "L'execution du test ne fonctionne pas"
    clean_tmp
    cd src
    make clean
    exit 1
fi

clean_tmp
cd src
make clean
echo_green "Test passé"
