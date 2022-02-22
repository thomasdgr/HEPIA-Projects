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
#include "jobs.h"

// variables globales pour stocker les id du pid et les utiliser dans le handler
int background_job_pid = 0;
int foreground_job_pid = 0;

/* objectifs: application d'un job et peut-etre d'une redirection avant de quitter la fonction,
 *            on attend d'etre sur que le job soit terminé
 * entrées: char** <array>, tableau des arguments entré par l'utilisateur
 * sorties: rien
 * limites des arguments: <array> doit contenir des commandes à executer et ne doit pas contenir de pipe ou de background job
 * conditions / effets de bords: <array> ne doit pas être NULL
 *                               peut quitter le programme au moindre problème (fork, open, close, dup2, execvp, setpgid, waitpgid)
 */
void apply_job(char** array){
    char* cmd = *array;
    char** cmd_array = array;
    int stat = 0;
    int ret = 0;
    // application et vérification du fork
    int pid = fork();
    if(pid == -1){
        red();
        printf("Fork failed: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        // code de l'enfant
        char* file = get_file_from_redirection(array);
        // detection de la redirection et récupération du fichier si besoin
        if(strcmp(file, "") != 0 && detect_pattern(array, ">")){
            // FAUX: int fd = open(file, O_WRONLY | O_CREAT, 0666);
            int fd = open(file, O_WRONLY | O_TRUNC, 0666);
            if(fd != -1){
                // controle du dup2
                if(dup2(fd, STDOUT_FILENO) == -1){
                    red();
                    printf("Failed to dup2 on '%s': %s\n", file, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                // controle de la fermeture du fichier
                if(close(fd) < 0){
                    red();
                    printf("Failed to close file '%s': %s\n", file, strerror(errno));
                    exit(EXIT_FAILURE);
                }
                // récupèration de la commande à executer
                cmd = get_cmd_from_array(array, ">");
                // conversion en tableau d'argument
                cmd_array = convert_input_to_array(cmd);
            // controle de l'ouverture du fichier
            } else{
                red();
                printf("Failed to open file '%s': %s\n", file, strerror(errno));
                exit(EXIT_FAILURE);
            }

        }
        // controle du bon fonctionnement de execvp
        if(execvp(*cmd_array, cmd_array) == -1){
            red();
            printf("Foreground job execvp exited with status: -1\n");
            exit(EXIT_FAILURE);
        }
    }
    // on assigne le pid en global au cas ou on en ai besoin dans le handler
    foreground_job_pid = pid;
    // verification du fonctionnement de setpgid
    if(setpgid(pid, getpid()) == -1){
        red();
        printf("Failed set pgid : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    // vérification du waitpid
    if((ret = waitpid(pid, &stat, 0)) == -1){
        red();
        printf("Issue on waitpid : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    purple();
    // en fonction du status, on affiche le code d'erreur et la manière dont le job s'est terminé
    if(WIFEXITED(stat)){
        printf("Foreground job %d terminated with status: %d\n", ret, WEXITSTATUS(stat));
    } else {
        printf("Foreground job %d exited with status: %d\n", ret, WEXITSTATUS(stat));
    }
}

/* objectifs: application de 2 jobs (on a nécéssairement un pipe dans le tableau)
 *            on attend d'etre sur que le job soit terminé pour quitter la fonction
              la sortie standard du premier enfant sera l'entrée standard du deuxième enfant
 * entrées: char** <array>, tableau des arguments entré par l'utilisateur
 * sorties: rien
 * limites des arguments: <array> doit contenir des commandes à executer et ne doit pas contenir de redirection ou de background job
 * conditions / effets de bords: <array> ne doit pas être NULL
 *                               peut quitter le programme au moindre problème (fork, pipe, open, close, dup2, execvp, setpgid, waitpgid)
 */
void apply_2_jobs(char** array){
    char* cmd = *array;
    char** cmd_array = array;
    int stat = 0;
    int ret = 0;
    int pipefd[2];
    // vérification du pipe
    if(pipe(pipefd) == -1){
        red();
        printf("Pipe failed: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }
    // application et vérification du fork
    int pid1 = fork();
    if(pid1 == -1){
        red();
        printf("Fork failed: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    } else if(pid1 == 0){
        // code de l'enfant + gestion des entrées sorties du pipe
        close(pipefd[1]);
        // controle du dup2
        if(dup2(pipefd[0], STDIN_FILENO) == -1){
            red();
            printf("Failed to dup2 on %d: %s\n", pipefd[0], strerror(errno));
            exit(EXIT_FAILURE);
        }
        close(pipefd[0]);
        // récupèration de la commande à executer
        cmd = get_second_cmd_from_array(array);
        // conversion en tableau d'argument
        cmd_array = convert_input_to_array(cmd);
        // controle du bon fonctionnement de execvp
        if(execvp(*cmd_array, cmd_array) == -1){
            red();
            printf("Second execvp exited with status: -1\n");
            exit(EXIT_FAILURE);
        }
    } else {
        // verification du fonctionnement de setpgid
        if(setpgid(pid1, getpid()) == -1){
            red();
            printf("Failed set pgid : %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        // on assigne le pid en global au cas ou on en ai besoin dans le handler
        foreground_job_pid = pid1;
        // on refait exactement la même maniuplation pour l'autre job à executer
        int pid2 = fork();
        if(pid2 == -1){
            red();
            printf("Fork failed: %s\n",strerror(errno));
            exit(EXIT_FAILURE);
        } else if(pid2 == 0){
            // gestion des entrées sorties du pipe pour le second job
            close(pipefd[0]);
            if(dup2(pipefd[1], STDOUT_FILENO) == -1){
                red();
                printf("Failed to dup2 on %d: %s\n", pipefd[1], strerror(errno));
                exit(EXIT_FAILURE);
            }
            close(pipefd[1]);
            cmd = get_cmd_from_array(array, "|");
            cmd_array = convert_input_to_array(cmd);
            if(execvp(*cmd_array, cmd_array) == -1){
                red();
                printf("First execvp exited with status: -1\n");
                exit(EXIT_FAILURE);
            } 
        }
        // verification du fonctionnement de setpgid
        if(setpgid(pid2, getpid()) == -1){
            red();
            printf("Failed set pgid : %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        // fermeture des entrées-sorties
        close(pipefd[0]);
        close(pipefd[1]);
        // vérification du waitpid
        if((ret = waitpid(pid2, &stat, 0)) == -1){
            red();
            printf("Issue on waitpid : %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        purple();
        // en fonction du status, on affiche le code d'erreur et la manière dont le job s'est terminé (1er job)
        if(WIFEXITED(stat)){
            printf("First foreground job %d terminated with status: %d\n", ret, WEXITSTATUS(stat));
        } else {
            printf("First foreground job %d exited with status: %d\n", ret, WEXITSTATUS(stat));
        }
    }
    // vérification du waitpid
    if((ret = waitpid(pid1, &stat, 0)) == -1){
        red();
        printf("Issue on waitpid : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    purple();
    // en fonction du status, on affiche le code d'erreur et la manière dont le job s'est terminé (2eme job)
    if(WIFEXITED(stat)){
        printf("Second foreground job %d terminated with status: %d\n", ret, WEXITSTATUS(stat));
    } else {
        printf("Second foreground job %d exited with status: %d\n", ret, WEXITSTATUS(stat));
    }
}

/* objectifs: application d'un background job (on a nécéssairement un "&" dans le tableau)
 *            pour vérifier le bon fonctionnement, un signal SIGCHLD est envoyé pour aller dans le handler de signaux
              et terminer le job correctement en affichant la manière dont il s'est terminé
 * entrées: char** <array>, tableau des arguments entré par l'utilisateur
 * sorties: rien
 * limites des arguments: <array> doit contenir des commandes à executer et ne doit pas contenir de redirection ou de pipe
 * conditions / effets de bords: <array> ne doit pas être NULL
 *                               peut quitter le programme au moindre problème (fork, pipe, open, close, dup2, execvp, setpgid)
 */
void apply_background_job(char** array){
    char* cmd = *array;
    char** cmd_array = array;
    int pid = fork();
    // vérification du fork
    if(pid == -1){
        red();
        printf("Fork failed: %s\n",strerror(errno));
        exit(EXIT_FAILURE);
    } else if(pid == 0){
        // ouverture et contrôle de /dev/null
        int fd = open("/dev/null", O_RDWR, 0666);
        if(fd != -1){
            // controle du dup2
            if(dup2(fd, STDIN_FILENO) == -1){
                red();
                printf("Failed to dup2 on '/dev/null' : %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            // vérification de la fermeture de /dev/null
            if(close(fd) < 0){
                red();
                printf("Failed to close /dev/null: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }
            // récupèration de la commande à executer
            cmd = get_cmd_from_array(array, "&");
            // conversion en tableau d'argument
            cmd_array = convert_input_to_array(cmd);
        // vérification de l'ouverture de /dev/null
        } else{
            red();
            printf("Failed to open /dev/null: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        // controle du bon fonctionnement de execvp
        if(execvp(*cmd_array, cmd_array) == -1){
            red();
            printf("Foreground job execvp exited with status: -1\n");
            exit(EXIT_FAILURE);
        }
    }
    // verification du fonctionnement de setpgid
    if(setpgid(pid, pid) == -1){
        red();
        printf("Failed set pgid : %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    // on assigne le pid en global au cas ou on en ai besoin dans le handler
    background_job_pid = pid;
}

/* objectifs: manager des signaux recus par le programme (SIGCHLD, SIGTERM, SIGINT, SIGQUIT, SIGHUP)
 *            en fonction du signal recu, on execute un code spécifique
 * entrées: int <sig>, le signal
 *          singinfo_t* <siginfo>, les information relatives au signal
 *          void* <context>, les informations relatives au contexte du signal
 * sorties: rien
 * limites des arguments: format standard du sigaction (pas nécéssairement de limites)
 * conditions / effets de bords: utilise 2 variables globales pour récupérer les pid des jobs
 *                               peut quitter le programme au moindre problème (killpg, write)
 *                               les signaux du handler doivent être initialisés avant de rentrer dans le handler
 */
void handler(int sig, siginfo_t* siginfo, void* context){
    // gestion du context du signal
    ucontext_t c = *(ucontext_t*) context;
    if(getcontext(&c) != 0){
        printf("Issue on context: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    int ret = 0;
    int stat = 0;
    // execution du code en fonction du signal passé en paramètre
    switch(sig){
        case SIGCHLD:
            if(siginfo->si_pid == background_job_pid){
                // vérification du waitpid
                if((ret = waitpid(siginfo->si_pid, &stat, 1)) == -1){
                    exit(EXIT_FAILURE);
                }
                // en fonction du status, on affiche le code d'erreur et la manière dont le job s'est terminé
                if(WIFEXITED(stat)){
                    char* buff = get_output_job(ret, WEXITSTATUS(stat), " terminated");
                    if(write(STDOUT_FILENO, buff, strlen(buff)) < 0){
                        exit(EXIT_FAILURE); 
                    }
                    free(buff);
                }else{
                    char* buff = get_output_job(ret, WEXITSTATUS(stat), " exited");
                    if(write(STDOUT_FILENO, buff, strlen(buff)) < 0){
                        exit(EXIT_FAILURE); 
                    }
                    free(buff);
                }
            }
            // NOTE IMPORTANTE: on doit faire un "Press ENTER..." à cause du flag SA_RESTART
            background_job_pid = 0;
            break;
        // on ignore délibérément le signal SIGTERM
        case SIGTERM:
            break;
        case SIGINT:
            // vérification du signal que l'on doit kill
            if(foreground_job_pid != 0 && background_job_pid == 0){
                // vérification du kill
                if(killpg(getpgid(foreground_job_pid),SIGTERM) == -1){
                    exit(EXIT_FAILURE);
                }
            }
            foreground_job_pid = 0;
            break;
        // on ignore délibérément le signal SIGQUIT
        case SIGQUIT:
            break;
        case SIGHUP:
            // vérification du kill
            if(killpg(getpid(),SIGINT) == -1){
                exit(EXIT_FAILURE);
            }
            // on quitte le programme
            exit(0);
            break;
        default:
            break;
    }
}