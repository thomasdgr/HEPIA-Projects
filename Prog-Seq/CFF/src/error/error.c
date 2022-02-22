/*******************************************************************************
			       ____
           /____ \               |  Projet : C_FF
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : fonction qui retourne des 
 __/  |    | \__/|               |    erreurs lors d'utilisations de fonction
(___) \.  _.\__. `\___           |    du projet
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	03/06/2020

\******************************************************************************/
#include "error.h"

void error_code_display(error_code error, char* function_name){
  char* value;
  switch(error){
    case out_of_bounds: value = "out_of_bounds"; break;
    case memory_error: value = "memory_error"; break;
    case uninitialized: value = "uninitialized"; break;
    case ok: break;
  } if(error != ok){
    printf("\n--> warning ! issue with vector (%s) while executing function : %s <--\n", value, function_name);
    exit(1);
  }
}