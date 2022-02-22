#ifndef JOBS_H
#define JOBS_H

#include "parsing.h"

/*Description: Fonction définssant les parmaètres nécessaires pour les jobs en fonction de
               la redirection, du pipe, du background ou rien du tout (par défaut).
               Suivante la présence de la redirection, pipe, background, ou rien du tout (par défaut),
               la définission des parmaètres diffère selon l'opérateur
 Entrée: struct arg comportant:
               - toutes les éléments que l'utilisateur a rentrée argv: char **
               - argc contient le nombre d'élément dans argv : int
               - index du pipe dans la chaîne de argv: int
               - index de la redirection dans la chaîne de argv: int
               - index du background dans la chaîne de argv: int
  Sortie: void -> exécute le programe demandé avec leurs arguments respectives (si il en a) et l'opérateur respectives (si il en a)
  Limites de l'entrée:
                - il ne peux comporter un ou aucun index valable parmi les 3 indexes.
  Effets de bord, préconditions, postconditions:
                effet de bords:
                    - exit le programme si il y a une erreur d'ouverture du fichier lors de la redirection
                préconditions:
                    - argv ne doit pas être null
                    - argc ne doit pas être 0*/
void cmdJobs(arg input);


/*Description:
      Fonction créant un enfant exécutant un programme avec ses arguments (si il en a), avec la redirection ou pas. Atttend que l'enfant finisse son travail à la fin.
  Entrée:
      - nom du programme: char*
      - un tableau des arguments du programme: char**
      - un descripteur de fichier: int
  Sortie: void -> voir Description
  Limites des entrées:
      - le tableau des arguments du programme contient le nom du programme, ses arguments (si il en a), un pointer NULL -> nécessaire pour execvp
      - le descripteur de fichier peut avoir -1 ou x, dans le cas:
                - -1, cela veut dire qu'il n'y a pas de redirection, donc on ne fait pas de dup2
                - x, cela veut dire qu'il y a une redirection, donc on fait dup2 sur le descripteur fichier ayant la valeur x.
  Effets de bord, préconditions, postconditions:
      préconditions :
          - le tableau des arguments doivent repecter un format: le nom du programme, ses arguments (si il en a), un pointer NULL nécessaire pour execvp
      Effet de bord :
          - quitte le programme si il y a un problème lors du fork, du execvp, du waitpid*/
void exec1Enfant(char *programme, char** argument, int fd);


/*Description:
      Fonction créant 2 enfants exécutant leurs programmes respective avec leurs arguments respective (si il en a), le sortie standard du jobs du premier enfant
      sera l'entrée standard du deuxième enfant (principe du pipe). Atttend que les enfants finissent leurs travaux à la fin.
  Entrée:
      - nom du premier programme: char*
      - un tableau des arguments du premier programme: char**
      - nom du deuxième programme: char*
      - un tableau des arguments du deuxième programme: char**
  Sortie: void -> voir Description
  Limites des entrées:
      - les tableaux des arguments du programme contiennent les noms du programmes à exécuter pour les enfants, ses arguments respectives (si il en a), un pointer NULL -> nécessaire pour execvp
  Effets de bord, préconditions, postconditions:
      préconditions :
          - les tableaux des arguments doivent repecter un format: le nom du programme, ses arguments (si il en a), un pointer NULL nécessaire pour execvp
      Effet de bord :
          - quitte le programme si il y a un problème lors du fork, du execvp, du waitpid, du pipe*/
void exec2Enfant(char *programme1, char** argument1, char*programme2, char** argument2);


/*Description:
      Fonction créant un enfant exécutant un programme avec ses arguments (si il en a) en background. Atttend que l'enfant finisse son travail à la fin.
  Entrée:
      - nom du programme: char*
      - un tableau des arguments du programme: char**
  Sortie: void -> voir Description
  Limites des entrées:
      - le tableau des arguments du programme contient le nom du programme, ses arguments (si il en a), un pointer NULL -> nécessaire pour execvp
  Effets de bord, préconditions, postconditions:
      préconditions :
          - avoir paramètrer la struct sigaction avec les flags SA_SIGINFO, et le handler sur une fonction donnée respectant le format demandé.
          - le tableau des arguments doivent repecter un format: le nom du programme, ses arguments (si il en a), un pointer NULL nécessaire pour execvp
      Effet de bord :
          - quitte le programme si il y a un problème lors du fork, du execvp
      postconditions:
          - on attend dans le handler que l'enfant puisse finir son jobs correctement.*/
void backgroundJobs(char *programme, char** argument);


/*Description:
      Fonction du handler
  Entrée:
      - le signal: int
      - les informations concernant le signal : siginfo_t
      - les informations du contexte du signal: void*
  Sortie: void -> voir le manuel du sigaction
  Limites des entrées:
      - cette fonction nécessite les entrées citées ci-dessus. C'est le format demandée lorsque qu'on fait le sigaction. (man sigaction)
  Effets de bord, préconditions, postconditions:
      préconditions :
          - d'avoir paramètrer le mask à SIGCHLD, et appeler le sigaction(SIGCHLD, &sigaction, NULL)
          - d'avoir stocké le pid de l'enfant censée faire en background dans une variable de globale.
      Effet de bord :
          - quitte le programme si il y a un problème lors du waitpid, ou write*/
void handler(int sig, siginfo_t *siginfo, void *context);
#endif
