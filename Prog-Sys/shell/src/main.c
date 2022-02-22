#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "parsing.h"
#include "jobs.h"
#include "builtin.h"


int main()
{
  char msg[100];
  arg input_parser;
  char cwd[PATH_MAX];

  //paramètrage du sigaction nécessaire pour le background jobs
  struct sigaction action;
  action.sa_flags = SA_SIGINFO | SA_RESTART;
  sigemptyset(&action.sa_mask);
  sigaddset(&action.sa_mask, SIGCHLD);
  sigaddset(&action.sa_mask, SIGINT);
  sigaddset(&action.sa_mask, SIGTERM);
  sigaddset(&action.sa_mask, SIGQUIT);
  sigaddset(&action.sa_mask, SIGHUP);

  action.sa_sigaction = &handler;

  if(sigaction(SIGCHLD, &action, NULL) == -1){
    perror ("sigaction");
    exit(EXIT_FAILURE);
  }
  if(sigaction(SIGINT, &action, NULL) == -1){
    perror ("sigaction");
    exit(EXIT_FAILURE);
  }
  if(sigaction(SIGTERM, &action, NULL) == -1){
    perror ("sigaction");
    exit(EXIT_FAILURE);
  }
  if(sigaction(SIGQUIT, &action, NULL) == -1){
    perror ("sigaction");
    exit(EXIT_FAILURE);
  }
  if(sigaction(SIGHUP, &action, NULL) == -1){
    perror ("sigaction");
    exit(EXIT_FAILURE);
  }
  //début shell
  while (1)
  {
    if(getcwd(cwd, sizeof(cwd)) == NULL) perror("getcwd");
    printf("%s$ ", cwd);
    if (fgets(msg, sizeof(msg), stdin) != NULL)
    {
      if (msg[0] != '\n')
      {
        input_parser = parser(msg);
        if (builtinOrJobs(input_parser)) cmdBuiltin(input_parser);
        else
        {
          input_parser.indexRedirection = isRedirection(input_parser);
          input_parser.indexPipe = isPipe(input_parser);
          input_parser.indexBackground = isBackground(input_parser);
          if (analyserJobs(input_parser)) cmdJobs(input_parser);
        }
        free(input_parser.argv);
      }
    }
  }
  exit(EXIT_SUCCESS);
}
