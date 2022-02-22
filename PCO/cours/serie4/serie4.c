#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 16

/********** EX 1 **********/
bool inside[2] = {false,false};
// id is the thread number (0 or 1) 
void prelude(int id){
    while (inside[1-id]){

    }
    inside[id] = true;
}
void postlude(int id){
    inside[id] = false;
}

// exclusion mutuelle = un seul thread en section critique (section du code accédant à des ressources partagées 
//                          -> les ressources sont accédées par un seul thread)
//                    + pas d'interblocage (plusieurs threads sont bloqués de manière permanente)
//                    + pas de famine (les threads n'ont pas la garantie d'accéder à leur section critique)

// le thread 0 peut rentrer en section critique à la ligne 17 ou 20
// pareil pour le thread 1 : la ressources est partagée entre plusieurs threads donc 
// l'exclusion mutuelle n'est pas satisfaite

/********** EX 2 **********/
int compare_and_swap(int *reg, int oldval, int newval){
    int old_reg_val = *reg;
    if(old_reg_val == oldval)
        *reg = newval;
    return old_reg_val;
}

// Cette fonction initialise le verrou passé en argument
void init_lock(bool* lock_ptr){
    *lock_ptr = 0;
}
// Cette fonction verrouille (acquiert) le verrou passé en argument
void acquire_lock(bool* lock_ptr){
    // tout marche car la fonction __sync... est atomique
    while(__sync_val_compare_and_swap(lock_ptr,0,1)); 
}
// Cette fonction déverrouille (relâche) le verrou passé en argument
void release_lock(bool* lock_ptr){
    lock_ptr = 0;
}

// A TERMINER

int main(int argc, char* argv[]){
    bool lock[2];
    init_lock(&lock);
    return EXIT_SUCCESS;
}