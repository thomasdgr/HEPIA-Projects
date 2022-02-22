#include <stdio.h>
#include <string.h>

int main(void)
{
    char buff[8];
    int pass = 0;

    printf("Exercice 1\n");

    printf("Enter the password: \n");
    gets(buff);

    if(strcmp(buff, "123456"))
    {
        printf("\nWrong Password\n");
    }
    else
    {
        printf ("\nCorrect Password\n");
        pass = 1;
    }

    if(pass)
    {
        printf ("Congratulation\n");
    }

    return 0;
}

