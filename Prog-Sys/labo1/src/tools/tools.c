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
#include "tools.h"

/* objectifs: récuperer le fichier vers lequel la redirection est faite. S'il n'y a
 *            pas de fichier ou pas de redirection, on retourne "".
 * entrées: char** <array>, tableau des arguments entré par l'utilisateur
 * sorties: un char* contenant le fichier trouvé ou "" si rien n'est trouvé
 * limites des arguments: <array> ne contient pas forcément le fichier à retourner
 * conditions / effets de bords: <array> ne doit pas être NULL
 *                               la fonction retourne quelque chose dans tous les cas
 */
char* get_file_from_redirection(char** array){
    char** ptr = array;
    for (char* c = *ptr; c; c=*++ptr){
        // detection de la redirection
        if(strcmp(c,">") == 0){
            c = *++ptr;
            if(c == NULL){
                // si aucun fichier n'est spécifié
                return "";
            } else {
                // si on trouve le fichier spécifié
                return c;
            }
        } else if(c == NULL){
            // pas de redirection trouvée
            return "";
        }
    }
    return "";
}

/* objectifs: detection d'un char* dans le tableau des arguments afin de
              determiner quel job doit être fait (foreground, background...)
 * entrées: char** <array>, tableau des arguments entré par l'utilisateur
            const char* <pattern>, le pattern à rechercher dans le tableau
 * sorties: bool, "true" si le pattern est trouvé, "false" sinon
 * limites des arguments: <array> ne contient pas forcément le pattern                  
 * conditions / effets de bords: <array> ne doit pas être NULL
 *                               <pattern> ne doit pas être NULL
 *                               si les conditions sont respectées, la fonction
 *                               retourne toujours un boolean
 */
bool detect_pattern(char** array, const char* pattern){
    char** ptr = array;
    for (char* c = *ptr; c; c=*++ptr){
        // detection du pattern
        if(strcmp(c,pattern) == 0){
            return true;
        }
    }
    return false;
}

/* objectifs: suppression des espaces (ou des "\t") avant on après la commande pour évitier
              que le programme plante à l'execution des commandes (ex: argument inattendu)
 * entrées: char* <s>, la chaine de caractère sur laquelle effectuer les modifications
 * sorties: rien
 * limites des arguments: <array> ne contient pas forcément d'éspaces
 * conditions / effets de bords: on modifie directement la valeur de <s>
 *                               <s> ne doit pas être null
 */
void remove_leading_trailing_spaces(char* s){
    // supression du "\n" s'il y en a un
    strtok(s,"\n");
    int  i,j;
    // décompte et supression des espaces avant la commande
    for(i = 0; s[i] == ' ' || s[i] == '\t'; i++){}
		
	for(j = 0; s[i]; i++){
		s[j++] = s[i];
	}
	s[j] = '\0';
    // décompte et supression des espaces après la commande
	for(i = 0; s[i] != '\0'; i++){
		if(s[i] != ' ' && s[i] != '\t'){
			j = i;
        }
	}
	s[j+1] = '\0';
}

/* objectifs: conversion d'un char* en un char** (tableau d'arguments)
 * entrées: char* <s>, la chaine de caractère sur laquelle on se base pour créer le tableau
 * sorties: char**, le tableau alloué en mémoire
 * limites des arguments: <s> peut ne rien contenir dans ce cas, on retourne un tableau vide
 *                        <s> doit contenir des espaces comme séparateurs sinon on a un tableau d'un seul élément
 * conditions / effets de bords: quitte le programme si le malloc n'est pas correctement réalisé
 *                               <s> ne doit pas être null
 */
char** convert_input_to_array(char* s){
    // suppression du "\n" si besoin
    strtok(s,"\n");
    // décompte du nombre d'éléments pour determiner la taille du tableau
    int count = 1;
    for (int i = 0;s[i] != '\0';i++){
        if (s[i] == ' ' && s[i+1] != ' ')
            count++;    
    }
    // allocation de la mémoire connaissant la taille et vérification
    char **array = malloc(sizeof(char*) * count);
    if (!array){
        red();
        fprintf(stderr, "Failed to malloc array\n");	
        exit(EXIT_FAILURE);
    }
    // remplissage du tableau avec les espaces comme séparateurs
	char *ptr = strtok(s, " ");
    int j = 0;
	while(ptr != NULL){
        array[j] = ptr;
		ptr = strtok(NULL, " ");
        j++;
	}
    return array;
}

/* objectifs: récupération de la commande située à gauche du pattern dans le tableau d'arguments
 * entrées: char** <array>, le tableau d'arguments
            const char* <pattern>, le séparateur pour la lecture de la commande (on exclue de la commande ">", "|" et "&")
 * sorties: char*, la commande à executer avant la redirection ou le pipe ou un char* vide si rien n'est trouvé
 * limites des arguments: <array> ne contient pas forcément le pattern, dans ce cas, un char* vide est retourné               
 * conditions / effets de bords: quitte le programme si le malloc n'est pas correctement réalisé
 *                               <array> ne doit pas être NULL
 *                               <pattern> ne doit pas être NULL
 */
char* get_cmd_from_array(char** array, const char* pattern){
    char** ptr = array;
    // allocation de la mémoire et vérification
    char* output = malloc(100 * sizeof(char));
    if (!output){
        red();
        fprintf(stderr, "Failed to malloc output\n");	
        exit(EXIT_FAILURE);
    }
    // ajout dans "output" des arguments situés avant le séparateur
    strcpy(output, *ptr);
    for (char* c = *++ptr; c; c=*++ptr){
        if(strcmp(c, pattern) == 0){
            return output;
        } else{
            // les arguments sont séparés par un espace
            strcat(strcat(output, " "),c);
        }
    }
    return "";
}

/* objectifs: récupération de la commande située à droite (forcément un pipe) du pattern dans le tableau d'arguments
 * entrées: char** <array>, le tableau d'arguments
 * sorties: char*, la commande à executer ou un string vide si rien n'est trouvé après le "|"
 * limites des arguments: <array> ne contient pas forcément le pattern, dans ce cas, un char* vide est retourné               
 * conditions / effets de bords: quitte le programme si le malloc n'est pas correctement réalisé
 *                               comme on récupère la commande de droite, on sait que le pattern est un pipe 
 *                               mais si ce n'est pas le cas, on retourne un char * vide
 *                               <array> ne doit pas être null
 */
char* get_second_cmd_from_array(char** array){
    char** ptr = array;
    // allocation de la mémoire et vérification
    char* output = malloc(100 * sizeof(char));
    if (!output){
        red();
        fprintf(stderr, "Failed to malloc output\n");	
        exit(EXIT_FAILURE);
    }
    // ajout dans "output" des arguments situés après le pipe
    for (char* c = *ptr; c; c=*++ptr){
        if(strcmp(c, "|") == 0){
            c = *++ptr;
            strcpy(output, c);
            for (char* c = *++ptr; c; c=*++ptr){
                // les arguments sont séparés par un espace
                strcat(strcat(output, " "),c);
            }
            return output;
        }
    }
    // s'il n'y a pas de pipe, on retourne un char* vide pour planter volotairement à l'éxécution
    // on déplace la detection de l'erreur à un moment plus opportunt
    return "";
}

/* objectifs: création du char* retourné pour indiquer l'etat du job depuis le handler
 * entrées: int <i>, le pid du processus
 *          int <j>, le status du processus
 *          char* <status>, toujours "terminated" ou "exited"
 * sorties: char*, la ligne à écrire dans STDOUT pour indiquer l'état du job
 * limites des arguments: rien
 * conditions / effets de bords: <status> ne doit pas être NULL
 */
char* get_output_job(int i, int j, char* status){
    char* res = malloc(sizeof(char) * 100);
    strcpy(res, "\nBackground job ");
    char tmp[10];
    // conversion du pid en char*
    sprintf(tmp, "%d", i);  
    strcat(res, tmp);
    strcat(res, status);
    strcat(res, " with status: ");
    // conversion du status en char*
    sprintf(tmp, "%d", j);  
    strcat(res, tmp);
    strcat(res, "\nPress Enter...");
    return res;
}