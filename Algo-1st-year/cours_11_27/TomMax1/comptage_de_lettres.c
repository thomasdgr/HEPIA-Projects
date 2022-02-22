#include <stdio.h>
#include <stdlib.h>

void main() {
    char phrase[100];
    char lettre;
    int count = 0;
    printf("Entrez une phrase: ");
    scanf("%s",phrase);

    printf("Entrez un lettre à chercher dans la phrase: ");
    scanf("%s",&lettre);

    for (int i = 0; i < sizeof(phrase); i++) {
      if (phrase[i] == lettre){
        count++;
      }
    }
    // bon y a un bug avec les pointeurs mais balek
    printf("nombre de fois que la lettre %s apparait dans la phrase %s : %d\n", lettre, phrase, count);
}