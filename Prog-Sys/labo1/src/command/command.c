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
#include "command.h"

/* objectifs: application de la commande built-in "cd"
 * entrées: char** <array>, tableau des arguments entré par l'utilisateur
 * sorties: rien
 * limites des arguments: "cd" doit être le premier argument dans <array>
 *                        le chemin doit exister dans le tableau sinon la commande n'est pas executé
 * conditions / effets de bords: <array> ne doit pas être NULL
 *                               ne quitte jamais pas le programme
 *                               n'execute pas la commande si le format n'est pas bon (ex: trop d'arguments)
 */
void apply_cd_command(char** array){
    char** ptr = array;
    for (char* c = *ptr; c; c=*++ptr){
        if(strcmp(c,"cd") == 0){
            continue;
        // récupération du chemin et vérification de la validité
        } else if(*++ptr == NULL){
            if(chdir(c) != 0){
                red();
                printf("cd: %s: No such file or directory\n", c);
            }
        // gestion d'erreur si le format n'est pas cohérent avec le "cd" original
        } else {
            red();
            printf("cd: too many arguments\n");
        }
    }
}

/* objectifs: dirriger l'execution des commandes en fonction des arguments présent dans <array>
 *            on lit les arguments et si on detecte un pattern, on appelle la fonction pour les pipes, les backgrounds jobs...
 *            la commande exit s'effectue avec un code spécifique donné par l'utilisateur
 * entrées: char** <array>, tableau des arguments entré par l'utilisateur
 * sorties: int, flag qui permet d'identifier si on fait un exit avec un code spécifique ou s'il y a eu un problème
 * limites des arguments: si le tableau est vide, on va retourner 1 ce qui va faire quitter le programme
 * conditions / effets de bords: <array> ne doit pas être NULL
 *                               s'il y a une erreur dans un des arguments, on ne plante pas ici, on continue
 *                               malgré tout pour planter à un moment plus opportunt (dans le execvp par exemple)
 */
int apply_command(char** array){
    char** ptr = array;
    for (char* c = *ptr; c; c=*++ptr){
        // detection de la commande "exit" (built-in)
        if(strcmp(c,"exit") == 0){
            c = *++ptr;
            if(c == NULL || atoi(c) == 0){
                exit(0);
            } else{
                // exit avec le code d'erreur spécifié en argument
                if(*++ptr == NULL){
                    return atoi(c);
                } else {
                    red();
                    printf("exit: too many arguments\n");
                }
            }
            return 0;
        // detection de la commande "cd" (built-in)
        } else if(strcmp(c,"cd") == 0){
            apply_cd_command(array);
            return 0;
        // on en déduit que la commande est un job
        } else{
            // detection d'un pipe
            if(detect_pattern(array, "|")){
                // vérification de la syntaxe du pipe (pas de redirection ou de tache de fond)
                if(detect_pattern(array, ">") || detect_pattern(array, "&")){
                    red();
                    printf("Impossible to redirect or execute background job inside pipe\n");
                } else {
                    // application des commandes avec le pipe
                    apply_2_jobs(array);
                }
            // detection et application d'un job en tache de fond
            } else if(detect_pattern(array, "&")){
                apply_background_job(array);
            }else{
                // application d'un job (peut aussi être une redirection)
                apply_job(array);
            }
            return 0;
        }
    }
    return 1;
}