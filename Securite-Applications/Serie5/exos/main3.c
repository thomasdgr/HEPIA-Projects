#include <stdio.h>
#include <string.h>
#include <limits.h>

int test(const char* input) {

    char buf[50];
    int canary = INT_MAX-1;
    int admin = 0;
    printf("canary=%d\n",canary);

    strcpy(buf, input);
    if(strcmp(buf, "123456"))
    {
        printf("Wrong Password\n");
    }
    else
    {
        printf ("Correct Password\n");
        admin = 1;
    }
    printf("canary=%x\nADMIN=%d\n",canary,admin);

    if (admin == 1 && canary == (INT_MAX-1)) {

        printf ("Congratulation\n");
    }
}


int main(int argc, char* argv[])
{

    printf("Exercice 3\n");

    if (argc != 2) 
    {
        printf("Usage: %s <code>\n", argv[0]);
        return 1;
    } 
    test(argv[1]);

    return 0;

}
