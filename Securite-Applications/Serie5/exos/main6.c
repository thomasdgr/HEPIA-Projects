#pragma check_stack(off)

#include <string.h>
#include <stdio.h> 

void test(const char* input)
{
    char buf1[100];
    char buf2[20] = "hello";

    strcpy(buf1, input);
    printf("%s\n", buf1);

}

int main(int argc, char* argv[])
{

    printf("Exercice 6\n");

    if (argc != 2) 
    {
        printf("Usage: %s <code>\n", argv[0]);
        return 1;
    } 
    test(argv[1]);

    return 0;
}
