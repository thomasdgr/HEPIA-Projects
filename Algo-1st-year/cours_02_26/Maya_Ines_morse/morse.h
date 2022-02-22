#ifndef MORSE_H
#define MORSE_H

typedef struct node
{
    char lettre;
    node *point;
    node *trait;
} node;

typedef struct arbre
{
    char lettre;
    node *point;
    node *trait;
    /* data */
} arbre ;

typedef arbre node;

arbre arbre_build(char *filename);
void placer(char *chaine, arbre *tree);
char decoder(char code[6], arbre tree);
char *encoder(char lettre, char **table);
void print(arbre tree, int niv);
char **table_build(char *filename);
void decoder_fichier(char *filename, arbre tree);
void encoder_fichier(char *filename, char **table);

#endif