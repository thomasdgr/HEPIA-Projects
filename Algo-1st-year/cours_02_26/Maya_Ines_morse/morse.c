#include <stdlib.h>
#include <stdio.h>
#include "morse.h"

arbre arbre_build(char *filename);
void placer(char *chaine, arbre *tree);

char decoder(char code[6], arbre tree){
    node *crt = &tree;
    int lg = strlen(code);
    for (int i = 0; i < lg; i++)
    {
        if ('.' == code[i])
        {
            crt = crt->point;
        }else if ('-' == code[i])
        {
            crt = crt->trait;
        } 
    }
    return crt->lettre;    
}

char *encoder(char lettre, char **table);

void print(arbre tree, int niv){
    // à gauche
    if (NULL != &tree->point)
    {
        print(&tree->point, niv+1);
    }
    for (int i = 0; i < niv; i++)
    {
        printf("  ");
    }
    printf("%s\n", &tree->lettre);
    // à droite
    if (NULL != *tree->trait)
    {
        print(&tree->trait, niv +1);
    }    
}

char **table_build(char *filename);
void decoder_fichier(char *filename, arbre tree);
void encoder_fichier(char *filename, char **table);