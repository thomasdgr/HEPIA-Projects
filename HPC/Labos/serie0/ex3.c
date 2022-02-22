#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct kek {
    char* value;
    char replace;
} kek;

char* func(kek *k){
    int length = strlen(k->value);
    char* new_value = malloc(sizeof(char) * length);
    for(int i = 0; i < length; i++){
        if(k->value[i] == ' '){
            new_value[i] = k->replace;	
        }
    }

    for(int i = 0; i < length/2; i++){
        char tmp = new_value[i];
        new_value[i] = new_value[length - i -1];
        new_value[length - i -1] = tmp;
    }

    return new_value;
}

void main(void){
    char *value = malloc(100 * sizeof(char));
    strcpy(value, "a tutut pouetpouet la voila, la totomobileuh\n");

    kek k = {value, ' '};

    char* new_value = func(&k);
    printf("%s\n", new_value);
}