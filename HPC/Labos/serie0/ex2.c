#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct kek {
    char* value;
    char replace;
} kek;

void func(kek *k){
    int length = strlen(k->value);
    for(int i = 0; i < length; i++){
        if(k->value[i] == ' '){
            k->value[i] = k->replace;	
        }
    }
}

void main(void){
    char *value = malloc(100 * sizeof(char));
    strcpy(value, "a tutut pouetpouet la voila, la totomobileuh\n");

    kek k = {value, ' '};

    func(&k);
    printf("%s\n", k.value);
}