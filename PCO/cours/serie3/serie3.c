#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 16

/********** EX 1 **********/
// oui c'est possible que P ne se termine jamais,
// on ne peut pas prédire dans quel thread il va rentrer en premier
// (attention à l'ordonancement des taches)

/********** EX 2 **********/
// l'instruction *addition* n'est pas attomique (c'est 2 MOV + 1 ADD + 2 MOV)
// les instructions permettant l'addition ne se font pas forcément en même temps
// mais ici cest pas possible on peut avoir soit 0 soit 3 (non-détérminisme)

/********** EX 3 **********/
// si x est partagé mais pas utilisé, on a 2 <= x <= 40 (car c'est sur 2 threads)
// si x est partagé et utilisé, on ne peut pas prévoir les bornes min-max

/********** EX 4 **********/
// atomicité, thread-safe et réentrance (voir cours)

/********** EX 5 **********/
// c'est pas réentrant car les déclarations sont statiques donc global au programme
// si on a des données globales elles sont partagées donc ce n'est pas réentrant
// on peut réécrire sur buffer[index] donc ce n'est pas non plus thread-safe


// changement de la fonction pour qu'elle soit thread-safe et réentrante
#define MAX_STRING_SIZE 256
char *strtoupper(char *string, char* res){
    //static char buffer[MAX_STRING_SIZE]; // static donc dans le tas
    int index;
    for (index = 0; string[index]; index++){
        //buffer[index] = toupper(string[index]);
        res[index] = toupper(string[index]);
    }
    //buffer[index] = 0;
    res[index] = 0;
    //return buffer;
    return res;
}

int main(int argc, char* argv[]){
    return EXIT_SUCCESS;
}