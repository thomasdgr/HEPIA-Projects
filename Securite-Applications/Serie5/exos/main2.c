#include <stdio.h>
#include <string.h>
#include <math.h>

int test(const char* input) {

    char buf[50];
    int number = 64;

    strcpy(buf, input);
    
    double squareRoot = sqrt(number);

    printf("Hello %s,\nThe square root of %d = %.2lf\n", buf, number, squareRoot);

    if (squareRoot > 9.9 && squareRoot < 10.1) {

        printf("Congratulation\n");
    }
}

int main(int argc, char* argv[])
{

    printf("Exercice 2\n");

    if (argc != 2) 
    {
        printf("Usage: %s <name>\n", argv[0]);
        return 1;
    } 
    test(argv[1]);

    return 0;

}
