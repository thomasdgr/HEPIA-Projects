// Nuclear Warhead code generator

#define NB_NUM 10
#define MIN_NUM 1
#define MAX_NUM 9

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    puts("Nuclear Warhead code generator");
    struct tm plop = {5,8,11,31,6,120};
    time_t kek = mktime(&plop);
    printf("%s", ctime(&kek));
    srand(kek);
    while(1) {
        puts("Press Any Key generate new code");
        getchar();  
        for(int i = 0; i < NB_NUM; i++){
            printf("%d ",rand() % (MAX_NUM - MIN_NUM + 1) + MIN_NUM);
        }
        printf("\n");
    }
    return 0;
}