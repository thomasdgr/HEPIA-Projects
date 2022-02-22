#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
    struct tm start = {0,0,0,1,0,120};
    time_t debut = mktime(&start);  
    time_t end = time(NULL);
  
    const char* CardColors[] = {"♠","♥","♦","♣"};
    const char* CardValues[] = {"2","3","4","5","6","7","8","9","J","Q","K","A"};
    char value[100] = "A♦ 4♣ J♠ 7♦ A♠ 3♠ ";
    char tmp1[100];
    char tmp2[100];

    for (time_t i = debut; i < end; i++) {
        srand(i);
        for (int j = 0; j < 6; j++) {
            strcpy(tmp1, CardColors[rand()% (sizeof(CardColors)/sizeof(CardColors[0]))]);
            strcat(tmp2, CardValues[rand()% (sizeof(CardValues)/sizeof(CardValues[0]))]);
            strcat(tmp2, tmp1);
            strcat(tmp2, " ");
        }
        if(strcmp(tmp2,value)==0){
            printf("%s",ctime(&i));
            printf("%s\n", tmp2);
            strcpy(tmp1, "");
            strcpy(tmp2, "");
            for(int k = 0; k < 4; k++){
              for (int l = 0; l < 6; l++) {
                  strcpy(tmp1, CardColors[rand()% (sizeof(CardColors)/sizeof(CardColors[0]))]);
                  strcat(tmp2, CardValues[rand()% (sizeof(CardValues)/sizeof(CardValues[0]))]);
                  strcat(tmp2, tmp1);
                  strcat(tmp2, " ");
              }
              printf("%s\n", tmp2);
              strcpy(tmp1, "");
              strcpy(tmp2, "");
            }
            break;
        }
        strcpy(tmp1, "");
        strcpy(tmp2, "");
    }
    return 0;
}
