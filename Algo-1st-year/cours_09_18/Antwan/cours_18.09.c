#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

bool is_prime(int input){
    
    if (input <= 0){
        return false;
    }

    if ( input == 1 || input == 2){
        return true;
    }

    for (int i = 2; i <= sqrt(input); i++){
        
        if (input % i == 0){
            return false;
        }
    }

    return true;
}

int main() {

    int myNumber = 7;
    int myOtherNumber = 16;
    int zero = 0;
    int myNegativeNumber = -7;

    if (is_prime(myNumber)){
        printf("%d is Prime! \n", myNumber);
    }else{
        printf("%d is not Prime! \n", myNumber);
    }


    if (is_prime(myOtherNumber)){
        printf("%d is Prime! \n", myOtherNumber);
    }else{
        printf("%d is not Prime! \n", myOtherNumber);
    }


    if (is_prime(zero)){
        printf("%d is Prime! \n", zero);
    }else{
        printf("%d is not Prime! \n", zero);
    }


    if (is_prime(myNegativeNumber)){
        printf("%d is Prime! \n", myNegativeNumber);
    }else{
        printf("%d is not Prime! \n", myNegativeNumber);
    }

}