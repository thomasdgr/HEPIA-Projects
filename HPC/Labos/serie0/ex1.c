#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void func(char *x, char *y){
    while(*y){
        *x++ = *y++;
    }
}

void main(void){
    char *jej = malloc(10 * sizeof(char));
    char *kek = malloc(10 * sizeof(char));
    strcpy(jej, "jej");
    strcpy(kek, "kek");

    func(kek, jej);
    printf("%s - %s\n", jej, kek);
}