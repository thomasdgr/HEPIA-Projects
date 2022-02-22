#include "jobs.h"

pid_t background_pid=-1;
pid_t chld = 0;
pid_t all_child[20];
int count = 1;
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
void cmdJobs(arg input)
{
  char programme[PATH_MAX];
  strcat(programme, input.argv[0]); // forme le nom du jobs
  char **argument = malloc((input.argc+1)*sizeof(char*)); //allocation du tableau d'arugment

  //si il y a seulement une redirection, donc on prend tout les arguments jusqu'à l'index de la redirection
  if (input.indexRedirection != -1 && input.indexPipe == -1 && input.indexBackground == -1)
  {
    //forme les arguments nécessaires pour execvp
    argument = realloc(argument, (input.indexRedirection+1)*sizeof(char*));
    for (int i = 0; i < input.indexRedirection; i++) argument[i] = input.argv[i];
    argument[input.indexRedirection] = NULL;
    int fd = open(input.argv[input.indexRedirection + 1], O_WRONLY|O_CREAT, 0666); //ouverture du fichier destination de redirection
    if(fd == -1) {
      perror("open: ");
      exit(EXIT_FAILURE);
    }
    //exécute le programme avec exec1Enfant
    exec1Enfant(programme, argument, fd);
  }
  //si il y a seulement une pipe, on détermine les arguments du premier jobs, et du deuxième jobs
  else if(input.indexPipe != -1 && input.indexRedirection == -1 && input.indexBackground == -1)
  {
    char programme1[PATH_MAX];
    strcat(programme1, input.argv[input.indexPipe+1]);

    //forme les arguments nécessaires pour execvp concernant le premier et le deuxième jobs
    argument = realloc(argument, (input.indexPipe+1)*sizeof(char*));
    char ** argument1 = malloc((input.argc-input.indexPipe)*sizeof(char*));

    for (int i = 0; i < input.indexPipe; i++) argument[i] = input.argv[i];
    argument[input.indexPipe] = NULL;
    for (int i = 0; i < input.argc-input.indexPipe-1; i++) argument1[i] = input.argv[input.indexPipe+i+1];
    argument1[input.argc-input.indexPipe-1] = NULL;

    //exécute le programme avec exec1Enfant et désalloue tous les mallocs pour le deuxième tableau des arguments
    exec2Enfant(programme, argument, programme1, argument1);
    strcpy(programme1, "");
    free(argument1);
  }
  // si il y a seulement un background, donc on prend tout les arguments jusqu'à l'index de la background.
  else if (input.indexBackground != -1 && input.indexPipe == -1 && input.indexRedirection == -1)
  {
    //forme les arguments nécessaires pour execvp
    argument = realloc(argument, (input.indexBackground+1)*sizeof(char*));
    for (int i = 0; i < input.indexBackground; i++) argument[i] = input.argv[i];
    argument[input.indexBackground] = NULL;

    //exécute le programme avec backgroundJobs
    backgroundJobs(programme, argument);
  }
  // sinon on prend tout les arguments du programme et on traite
  else
  {
    //forme les arguments nécessaires pour execvp
    for (int i = 0; i < input.argc; i++) argument[i] = input.argv[i];
    argument[input.argc] = NULL;

    //exécute le programme, vu qu'il n'y a pas de redirection, on met -1 dans le dernier argument pour signaler qu'il y a pas de fichier à rediriger
    exec1Enfant(programme, argument, -1);
  }

  //réinitialisation des nom du programme et le tableau des arguments
  strcpy(programme, "");
  free(argument);
}


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
void exec1Enfant(char *programme, char** argument, int fd)
{
  //création de l'enfant
  pid_t en_pid = fork();

  //gestion d'erreur pour le fork
  if (en_pid == -1) {
    perror("fork problème");
    exit(EXIT_FAILURE);
  }

  // rentre dans l'enfant
  if (en_pid == 0) {
    //redirection si condition respecté
    if(fd != -1) {
      if(dup2(fd, STDOUT_FILENO) == -1){
        perror("dup2");
        exit(EXIT_FAILURE);
      }
      close(fd);
    }

    //exécute le programme avec ses arguments, si erreur, quitte le programme
    if (execvp(programme, argument) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
  }
  //set pour sigint
  chld = en_pid;
  //définisse le pgid
  if(setpgid(en_pid, en_pid) == -1)
  {
      perror("setpgid");
      exit(EXIT_FAILURE);
  }
  //set pour le sighup
  all_child[count-1] = en_pid;
  count++;
  //attend que l'enfant finisse son job
  int wstatus;
  if (waitpid(en_pid, &wstatus, WUNTRACED | WCONTINUED) == -1) {
    perror("waitpid");
    exit(EXIT_FAILURE);
  }
  //reset pour le sighup
  count--;
  all_child[count-1] = 0;
  //affiche l'état de l'enfant lorsque le job est fini
  printf("Foreground job exited with %d\n", WEXITSTATUS(wstatus));
}


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
void exec2Enfant(char *programme1, char** argument1, char*programme2, char** argument2)
{
  pid_t en1_pid;
  pid_t en2_pid;
  int fd[2];
  int wstatus;
  int wstatus1;
  //création du pipe
  if (pipe(fd) == -1) {
    perror("pipe problème");
    exit(EXIT_FAILURE);
  }
  //appelle fonction fork
  en1_pid = fork();
  if (en1_pid == -1) {
    perror("fork problème");
    exit(EXIT_FAILURE);
  }

  if (en1_pid == 0) {
    //on éxécute le programme à droite, redirige l'entrée standard vers la sortie du pipe
    close(fd[1]);
    if(dup2(fd[0], STDIN_FILENO) == -1){
      perror("dup2");
      exit(EXIT_FAILURE);
    }
    close(fd[0]);
    if (execvp(programme2, argument2) == -1) {
      perror("execve2");
      exit(EXIT_FAILURE);
    }
  }else
  {
    //set le pgid à pid lui-même
    if(setpgid(en1_pid, en1_pid) == -1)
    {
        perror("setpgid");
        exit(EXIT_FAILURE);
    }
    //set pour le sigint
    chld = en1_pid;
    //set pour le sighup par rapport à child1
    all_child[count-1] = en1_pid;
    count++;
    //rappelle fonction fork
    en2_pid = fork();
    if(en2_pid == 0)
    {
      //on exécute le programme à gauche, redirige sortie standard vers l'entrée du pipe
      close(fd[0]);
      if(dup2(fd[1], STDOUT_FILENO) == -1){
        perror("dup2");
        exit(EXIT_FAILURE);
      }
      close(fd[1]);
      if (execvp(programme1, argument1) == -1) {
        perror("execve1");
        exit(EXIT_FAILURE);
      }
    }
    //set pour le sighup par rapport à child1
    all_child[count-1] = en2_pid;
    count++;
    //set le pgid à pid de son frère
    if(setpgid(en2_pid, en1_pid) == -1)
    {
        perror("setpgid");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);

    //attend que les enfants finissent leurs jobs
    if (waitpid(en1_pid, &wstatus, WUNTRACED | WCONTINUED ) == -1) {
      perror("waitpid1 problème");
      exit(EXIT_FAILURE);
    }
    //reset sigHUp
    count--;
    all_child[count-1] = 0;

    if (waitpid(en2_pid, &wstatus1, WUNTRACED | WCONTINUED ) == -1) {
      perror("waitpid2 problème");
      exit(EXIT_FAILURE);
    }
    //rest sighup
    count--;
    all_child[count-1] = 0;

    //affiche l'état des enfants lorsque leurs jobs est fini
    printf("Foreground job1 exited with %d\n", WEXITSTATUS(wstatus));
    printf("Foreground job2 exited with %d\n", WEXITSTATUS(wstatus1));
  }
}


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
void backgroundJobs(char *programme, char** argument)
{
  //ouverture du fichier "dev/null/"
  int fd = open("/dev/null", O_WRONLY, 0666); //ouverture du fichier /dev/null
  if(fd == -1) {
    perror("open: ");
    exit(EXIT_FAILURE);
  }

  //création de l'enfant:
  pid_t en_pid = fork();
  if (en_pid == -1) {
    perror("fork problème");
    exit(EXIT_FAILURE);
  }
  //enfant
  if (en_pid == 0)
  {
    //redirige la sortie standard vers "dev/null/
    if(fd != -1) {
      if(dup2(fd, STDOUT_FILENO) == -1){
        perror("dup2");
        exit(EXIT_FAILURE);
      }
      close(fd);
    }
    //exécute le nom du programme avec le tableau des arguments
    if (execvp(programme, argument) == -1) {
      perror("execvp");
      exit(EXIT_FAILURE);
    }
  }
  all_child[count-1] = en_pid;
  count++;
  //parent, attribution global, mettre à jour le pgid.
  background_pid=en_pid;
  if(setpgid(en_pid, en_pid) == -1)
  {
      perror("setpgid");
      exit(EXIT_FAILURE);
  }
}

/*Description:
      Fonction du handler, gère les signaux: SIGCHLD, SIGINT, SIGUP. ignore SIGTERM et SIGQUIT
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
void handler(int sig, siginfo_t *siginfo, void *context)
{
  int wstatus;
  ucontext_t extract_contexte = (*(ucontext_t*) context);
  if (getcontext(&extract_contexte) == -1)
  {
    perror("getcontext");
    exit(EXIT_FAILURE);
  }
  switch (sig)
  {
    case SIGCHLD:
      if (background_pid == siginfo->si_pid)
      {
        //attend que l'enfant en background finisse son jobs
        if (waitpid(siginfo->si_pid, &wstatus, WUNTRACED | WCONTINUED ) == -1) {
          perror("waitpid background problème");
          exit(EXIT_FAILURE);
        }
        count--;
        all_child[count-1] = 0;
        //signal que le job en tache de fon finisse.
        if (write(STDOUT_FILENO, "\nBackground job exited\n", 23)<0) {
          perror("write");
          exit(EXIT_FAILURE);
        }
        //réinialise du background_pid
        background_pid=0;
      }
      break;
    case SIGINT:
      if (chld != 0 && background_pid == 0) {
        if (killpg(getpgid(chld),SIGTERM) == -1)
        {
          perror("killpg");
          exit(EXIT_FAILURE);
        }
      }

      if (write(STDOUT_FILENO, "\n", 1)<0) {
        perror("write");
        exit(EXIT_FAILURE);
      }
      chld = 0;
      break;
    case SIGHUP:
      for(int i = 0; i < count; i++)
      {
        kill(all_child[i], SIGTERM);
      }
      kill(siginfo->si_pid, SIGTERM);
      break;
    default:
      //ignoreed for SIGQUIT and SIGTERM
      break;
  }
}
