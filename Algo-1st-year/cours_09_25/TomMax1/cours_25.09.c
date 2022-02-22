#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void main()
{
    char mot1[30] = "";
    char mot2[30] = "";
    printf("Entrez un mot : ");
    scanf("%s", mot1);
    printf("Entrez un second mot : ");
    scanf("%s", mot2);

    palindrome(mot1);
    anagramme(mot1, mot2);
}

int anagramme(char mot1[], char mot2[])
{
    printf("Les mots %s et %s", mot1, mot2);

    // tri de mot1
    int ind_min;
    for (int i = 0; i < sizeof(mot1); i++)
    {
        ind_min = i;
        for (int k = i + 1; k < sizeof(mot1)+1; k++)
        {
            if (mot1[k] < mot1[ind_min])
            {
                ind_min = k;
            }
        }
        int tmp = mot1[i];
        mot1[i] = mot1[ind_min];
        mot1[ind_min] = tmp;
    }

    // tri de mot2
    for (int i = 0; i < sizeof(mot2); i++)
    {
        ind_min = i;
        for (int k = i + 1; k < sizeof(mot2)+1; k++)
        {
            if (mot2[k] < mot2[ind_min])
            {
                ind_min = k;
            }
        }
        int tmp = mot2[i];
        mot2[i] = mot2[ind_min];
        mot2[ind_min] = tmp;
    }

    bool egal = true;
    for (int i = 0; i < 20; i++)
    {
        if (mot1[i] != mot2[i])
        {
            egal = false;
            break;
        }
    }
    egal = (strcmp(mot1, mot2) == 0);

    if (egal)
    {
        printf(" sont des anagrammes\n");
    }
    else
    {
        printf(" ne sont pas des anagrammes\n");
    }
    return 1;
}

int palindrome(char mot1[])
{
    printf("Le mot %s", mot1);

    bool palindrome = true;
    int first_idx = 0;
    int last_idx = strlen(mot1) - 1;

    while (first_idx < last_idx)
    {
        if (mot1[first_idx] != mot1[last_idx])
        {
            palindrome = false;
            break;
        }
        first_idx += 1;
        last_idx -= 1;
    }
    if (palindrome)
    {
        printf(" est un palindrome\n");
    }
    else
    {
        printf(" n'est pas un palindrome\n");
    }
    return 1;
}
