#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int secureShuffle(int size, int array[size]){
    int rnd = rand();
    for(int i = 0; i < rnd % 5 + 2; i++){
       for(int j = 0; j < size; j++){
            int value = rand() % size;
            int tmp = array[j];
            array[j] = array[value];
            array[value] = tmp;
        } 
    }
}

int main(){
    struct tm start = {0,0,0,1,6,119};
    struct tm stop = {0,0,0,1,0,120};
    time_t debut = mktime(&start);  
    time_t end = mktime(&stop);
    bool flag = true;
    int count = 0;
    for (time_t crt = debut; crt < end; crt++) {
        if(flag){
            srand(crt);
        }
        int numbers[50];
        int luckyNumbers[12];
        for(int i = 1; i <= 50; i++){
            numbers[i-1] = i;
            if(i < 13){
                luckyNumbers[i-1] = i;
            }
        }
        secureShuffle(50, numbers);
        secureShuffle(12, luckyNumbers);
        if(numbers[0] == 17 && numbers[1] == 38 && numbers[2] == 33 &&
           numbers[3] == 22 && numbers[4] == 26 && 
           luckyNumbers[0] == 5 && luckyNumbers[1] == 9){
            printf("%s", ctime(&crt));
            flag = false;
        }
        if(flag == false){
            printf("%d %d %d %d %d - %d %d\n",numbers[0], numbers[1],
            numbers[2], numbers[3], numbers[4], luckyNumbers[0], luckyNumbers[1]);
            count++;
            if(count == 5){
                break;
            }
        }
    }
    return 0;
}