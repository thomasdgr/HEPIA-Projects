#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/time.h>

int main () {
    char password[] = "...............";
	char command[30] = "./crackme5 ";
    char input[30];
    char theGoodOne = '.';
    int status = 1;
    double max_time = 0.0;

    struct timeval start, stop;
    double secs = 0;

    for(int i = 0; i < 15; i++){
        for (unsigned char k = 0; k < 255; k++){
            if (isalpha(k)) {
                password[i] = k;
	            strcpy(input, command);
	            strcat(input, password);
                strcat(input, " > /dev/null");
                for(int j = 0; j < 4; j++){
                    gettimeofday(&start, NULL);
                    status = system(input);
                    gettimeofday(&stop, NULL);
                    secs += (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
                }
                secs = secs / 4;
                if(secs > max_time){
                    max_time = secs;
                    theGoodOne = k;
                }
                secs = 0.0;
                strcpy(input,"");
            }
        }
        max_time = 0.0;
        password[i] = theGoodOne;
        strcpy(input,"");
    }
    printf("%s\n",password);
    return 0;
}