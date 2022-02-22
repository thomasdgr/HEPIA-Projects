#pragma check_stack(off)

#include <string.h>
#include <stdio.h> 

void test(const char* input)
{
    char buf[10];

    strcpy(buf, input);
    printf("%s\n", buf);

}

void secret(void)
{
    printf("Congratulation\n");
}

int main(int argc, char* argv[])
{


    printf("Exercice 5\n");

    printf("Address of test = %p\n", test);
    printf("Address of secret = %p\n", secret);

    if (argc != 2) 
    {
        printf("Usage: %s <code>\n", argv[0]);
        return 1;
    } 
    test(argv[1]);

    return 0;
}
