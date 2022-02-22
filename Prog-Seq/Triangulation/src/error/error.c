/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |  
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              | 
    | |    |     |               |  Descripition : Gestion des error_code qui permettent de vérifier qu'une 
 __/  |    | \__/|               |                 fonction vector/vector_list s'effectue sans problemes
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |  
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020		
                                 
\**********************************************************************************************************************************************************************************************************************************/
#include "../vector/vector/vector.h"

void error_code_display(error_code error, char* function_name){
  char* value;
  switch(error){
    case out_of_bounds: value = "out_of_bounds"; break;
    case memory_error: value = "memory_error"; break;
    case uninitialized: value = "uninitialized"; break;
    case ok: break;
  } if(error != ok){
    printf("\n--> warning ! issue with vector (%s) while executing function : %s <--\n", value, function_name);
    // il est préférable de faire planter le programme pour etre sur de pas avoir de comportement indéterminé plus tard
    exit(1);
  }
}
