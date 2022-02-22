#pragma check_stack(off)

#include <stdio.h>
#include <string.h>

int test(const char* input) {

    char buf[50];
    char can[] = {'P', 'o', 'u', 'e', 't'};
    int admin = 0;

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
    printf("can=%s\nADMIN=%d\n",can,admin);


    if (admin == 1 && can[0] == 'P' && can[1] == 'o' && can[2] == 'u' && can[3] == 'e' && can[4] == 't') {
        printf ("Congratulation\n");
    }
}


int main(int argc, char* argv[])
{

    printf("Exercice 4\n");

    if (argc != 2) 
    {
        printf("Usage: %s <code>\n", argv[0]);
        return 1;
    } 
    test(argv[1]);

    return 0;

}

