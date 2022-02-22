#ifndef BUILTIN_H
#define BUILTIN_H

#include "parsing.h"

/*Description: Fonction qui quitte le shell, qui affiche le répertoire courrant de l'utilisateur, change le répertoire
               selon l'entrée argv de l'utilisateur
 Entrée: struct arg comportant:
               - toutes les éléments que l'utilisateur a rentrée argv: char **
               - argc contient le nombre d'élément dans argv : int
               - index du pipe dans la chaîne de argv: int
               - index de la redirection dans la chaîne de argv: int
               - index du background dans la chaîne de argv: int
  Sortie: void -> exécute la commande demandé, rien sinon
  Limites de l'entrée:
                - il ne peux comporter un ou aucun index valable parmi les 3 indexes.
  Effets de bord, préconditions, postconditions:
                effet de bords:
                    - exit le programme si l'utilisateur rentre un exit
                préconditions:
                    - doit déterminer au préalable si le premier élément du argv est un commande builtin.
                    - argv ne doit pas être null
                    - argc ne doit pas être 0*/
void cmdBuiltin(arg input);


/*Description: Fonction qui affiche le répertoire où l'utilisateur se trouve
  Entrée: None
  Sortie: void -> affiche le répertoire courant
  Effet bord: affiche l'erreur si getcwd faites une erreur*/
void pwd();


/*Description: Fonction qui change de répertoire en fonction où l'utilisateur se trouve
  Entrée: le dossier de destination: char*
  Sortie: void -> change de répertoire si le path existant
  Limites de l'entrée: le dossier de destination doit existe ou le path doit exister
  Effets de bord, préconditions, postconditions:
                effet de bords:
                    - affiche l'erreur si chdir faites une erreur
                préconditions:
                    - doit déterminer au préalable si il existe un dossier de destination*/
void cd(char * dest_directory);
#endif
