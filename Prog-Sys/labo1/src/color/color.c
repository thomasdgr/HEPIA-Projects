/*****************************************************************************
		         ____
           /____ \         | Projet : TP sur la création d'un shell en C 
           | _ _`\|        |        
    .-.   `| O O |         | Auteur : Thomas DAGIER
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Utiliser les notions abordées en
(___)  )\/  \_____/  ~\.   |                cours pour executer les commandes
(___) . \   `         `\   |                et programmes du systeme
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 03/05/2021

*****************************************************************************/
#include "color.h"

// en fonction de la fonction appellée, on va colorer le contenu du printf() qui sera affiché dans STDOUT

void black(){
  printf("\033[0;30m");
}

void red(){
  printf("\033[0;31m");
}

void green(){
  printf("\033[0;32m");
}

void yellow(){
  printf("\033[0;33m");
}

void blue(){
  printf("\033[0;34m");
}

void purple(){
  printf("\033[0;35m");
}

void cyan(){
  printf("\033[0;36m");
}

void white(){
  printf("\033[0;37m");
}

void reset(){
  printf("\033[0m");
}