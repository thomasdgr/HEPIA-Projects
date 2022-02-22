#include "parsing.h"

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
arg parser (char * STDinput)
{
  //initilisation des éléments de ma structure
  arg input;
  int argc = 0;
  input.argv = malloc(strlen(STDinput)*sizeof(char*));

  // séparant chaque mot de l'entrée de l'utilisateur, le met dans un tableau
  char *token = strtok(STDinput, " \n\t\f");

  while(token != NULL)
  {
    input.argv[argc] = token;
    token = strtok(NULL, " \n");
    argc++;
  }
  //réalloue argv et attribution du nombre argument dans argc
  input.argv = realloc(input.argv, argc*sizeof(char*));
  input.argc = argc;
  return input;
}


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
bool builtinOrJobs(arg input_parser)
{
  char *commande_rentre = input_parser.argv[0];
  return strcmp(commande_rentre, "exit") == 0 || strcmp(commande_rentre, "cd") == 0 || strcmp(commande_rentre, "pwd") == 0;
}


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
int isRedirection(arg input_parser)
{
  for (int i = 0; i < input_parser.argc; i++) {
    if(strcmp(input_parser.argv[i], ">") == 0)
    {
      return i;
    }
  }
  return -1;
}

int isPipe(arg input_parser)
{
  for (int i = 0; i < input_parser.argc; i++) {
    if(strcmp(input_parser.argv[i], "|") == 0 )
      return i;
  }
  return -1;
}

int isBackground(arg input_parser)
{
  for (int i = 0; i < input_parser.argc; i++) {
    if(strcmp(input_parser.argv[i], "&") == 0)
      return i;
  }
  return -1;
}


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
bool analyserJobs(arg input_parser)
{
  if (input_parser.indexRedirection != -1 && input_parser.indexRedirection+1 == input_parser.argc)
  {
    printf("erreur: il manque un fichier de destination pour la redirection\n");
    return false;
  }
  else if (input_parser.indexPipe != -1 && input_parser.indexPipe+1 == input_parser.argc)
  {
    printf("erreur: il manque un autre jobs\n");
    return false;
  }
  else if(input_parser.indexPipe != -1 && (input_parser.indexRedirection != -1 || input_parser.indexBackground != -1))
  {
    printf("erreur: pipe et (redirection ou background) ne peut pas être exécuté en même temps\n");
    return false;
  }
  else if(input_parser.indexRedirection != -1 && input_parser.indexBackground != -1)
  {
    printf("erreur: redirection et background ne peut pas être exécuté en même temps\n");
    return false;
  }
  else return true;
}
