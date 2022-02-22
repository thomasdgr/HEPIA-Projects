#ifndef PARSING_H
#define PARSING_H

#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <ucontext.h>

typedef struct arg{
  int argc;
  char** argv;
  int indexRedirection;
  int indexPipe;
  int indexBackground;
}arg;


/*Description: Fonction qui parse l'entrée de l'utilisateur en une structure arg
  Entrée: chaîne de charactère que l'utilisateur a rentrée: char *
  Sortie: struct arg comportant:
                - argv: tableau de chaine de charactère
                - argc: int
                - index du pipe dans la chaîne de argv: int
                - index de la redirection dans la chaîne de argv: int
                - index du background dans la chaîne de argv: int
  Limites de l'entrée:
                - la chaîne de charactère ne doit pas être null
  Effets de bord, préconditions, postconditions:
                - préconditions: la chaine de charactère rentrée n'est pas une retour à la ligne (ou NULL)*/
arg parser (char * STDinput);


/*Description: Fonction qui détermine si c'est une commande builtin ou Jobs
  Entrée: struct arg comportant:
                - toutes les éléments que l'utilisateur a rentrée argv: char **
                - argc contient le nombre d'élément dans argv : int
                - index du pipe dans la chaîne de argv: int
                - index de la redirection dans la chaîne de argv: int
                - index du background dans la chaîne de argv: int
  Sortie: bool, vrai si commande builtin sinon, faux
  Limites de l'entrée:
                - il ne peux comporter un ou aucun index valable parmi les 3 indexes.*/
bool builtinOrJobs(arg input_parser);


/*Description des 3 fonctions ci-dessous: Les fonctions qui déterminent l'index dans argv les opérateurs: ">" "|" "&". Par défaut, ces indexs valent -1.
  Entrée: struct arg comportant:
                - toutes les éléments que l'utilisateur a rentrée argv: char **
                - argc contient le nombre d'élément dans argv : int
                - index du pipe dans la chaîne de argv: int
                - index de la redirection dans la chaîne de argv: int
                - index du background dans la chaîne de argv: int
  Sortie: index du symbole, sinon -1
  Limites de l'entrée:
                - il ne peux comporter un ou aucun index valable parmi les 3 indexes.*/
int isRedirection(arg input_parser);
int isPipe(arg input_parser);
int isBackground(arg input_parser);


/*Description: Fonction qui analyse les entrées de l'utilisateur selon les besoins des opérateurs : ">" "|" "&" (si il n'en a)
  Entrée: struct arg comportant:
                - toutes les éléments que l'utilisateur a rentrée argv: char **
                - argc contient le nombre d'élément dans argv : int
                - index du pipe dans la chaîne de argv: int
                - index de la redirection dans la chaîne de argv: int
                - index du background dans la chaîne de argv: int
  Sortie: bool -> vrai si les conditions sont respectés, sinon false.
  Limites de l'entrée:
                - il ne peux comporter un ou aucun index valable parmi les 3 indexes.*/
bool analyserJobs(arg input_parser);
#endif
