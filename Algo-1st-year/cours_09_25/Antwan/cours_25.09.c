#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int PPCM(int a, int b)
{
    int a_origin = a;
    int b_origin = b;

    while (a != b)
    {
        if (a < b)
        {
            a += a_origin;
        }
        else
        {
            b += b_origin;
        }
    }

    return a;
}

int PGCD(int a, int b)
{
    //Algorithme d'Euclide
    int reste = 0;
    int tmp = a;

    do
    {
        reste = a % b;
        a = b;
        if (reste > 0)
            b = reste;
    } while (reste != 0);

    return b;
}

bool is_palindrome(char *str, int len)
{
    char strinverse[len];

    for (int i = 0; i < len; i++)
    {
        strinverse[len - 1 - i] = str[i];
    }

    for (int i = 0; i < len; i++)
    {
        if (strinverse[i] != str[i])
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int a = 12;
    int b = 15;
    printf("PPCM de %d et %d : %d \n", a, b, PPCM(a, b));

    int c = 35;
    int d = 60;
    printf("PGCD de %d et %d : %d \n", c, d, PGCD(d, c));

    char str[4] = "lolp";
    if (is_palindrome(str, 4))
    {
        printf("%s is a palindrome! \n", str);
    }
    else
    {
        printf("%s is not a palindrome! \n", str);
    }

    char str2[5] = "lolol";
    if (is_palindrome(str2, 5))
    {
        printf("%s is a palindrome! \n", str2);
    }
    else
    {
        printf("%s is not a palindrome! \n", str2);
    }

    int size = 20;
    bool crible[size];
    for (int i = 0; i < size; i++)
    {
        crible[i] = true;
    }

    //Crible
    for (int i = 2; i < sqrt(size); i++)
    {
        if (crible[i])
        {
            for (int j = i * i; j < size; j += i)
                crible[j] = false;
        }
    }

    printf("Prime numbers from 0 to %d are: ", size);
    for (int i = 1; i < size; i++)
    {
        if (crible[i])
            printf("%d, ", i);
    }
    printf("\n");
}