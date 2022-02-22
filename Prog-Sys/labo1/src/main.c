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
#include "command/command.h"


/* CORRECTION:
 * -> ajouter plus de commentaires
 * -> ne pas retourner de 0 en cas d'erreur dans une fonction
 */


/* objectifs: boucle infinie qui lit l'input entréé par l'utilisateur, 
              la convertit en tableau de char* et l'envoie vers le manager des tâches
 * entrées: rien
 * sorties: rien
 * limites des arguments: rien
 * conditions / effets de bords: rien
 */
int main(){
    //création du sigaction pour les signaux à intercepter
    struct sigaction sa;
    // flag pour résoudre le problème de bloquage dans le handler
    sa.sa_flags = SA_SIGINFO | SA_RESTART;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGCHLD);
    sigaddset(&sa.sa_mask, SIGTERM);
    sigaddset(&sa.sa_mask, SIGQUIT);
    sigaddset(&sa.sa_mask, SIGINT);
    sigaddset(&sa.sa_mask, SIGHUP);
    sa.sa_sigaction = &handler;
    if(sigaction(SIGCHLD, &sa, NULL) == -1){
        exit(EXIT_FAILURE); 
    }
    if(sigaction(SIGTERM, &sa, NULL) == -1){
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGQUIT, &sa, NULL) == -1){
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGINT, &sa, NULL) == -1){
        exit(EXIT_FAILURE);
    }
    if(sigaction(SIGHUP, &sa, NULL) == -1){
        exit(EXIT_FAILURE);
    }
    char input[512];
    char** array;
    int res = 0;
    char path[PATH_MAX];
    yellow();
    printf("Oppening shell...\n");
    while (1){
        blue();
        printf("thomas@shell:");
        green();
        if (getcwd(path, sizeof(path)) != NULL) {
            printf("%s", path);
        }
        white();
        printf("$ ");
        // récupération des arguments entrés par l'utilisateur
        if(fgets(input, 512, stdin) == NULL){
            continue;
        }
        // on supprime de la chaine les espaces avant ou après
        remove_leading_trailing_spaces(input);
        // on s'assure que la commande ne termine pas par un "\n"
        input[ strcspn( input, "\n" ) ] = '\0';
        if(input[0] != '\0'){
            // conversion d'un char* en char**
            array = convert_input_to_array(input);
            // application de la commande
            res = apply_command(array);
            // quelque chose en lien avec la lecture du tableau n'a pas marché
            if(res == 1) return EXIT_FAILURE;
            // on quitte le programme avec le code renseigné par l'utilisateur
            if(res != 0) {free(array); exit(res);}
            free(array);
        }
    }
    free(array);
    return EXIT_SUCCESS;
}
