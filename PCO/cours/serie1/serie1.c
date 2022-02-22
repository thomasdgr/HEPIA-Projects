#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#define NUM_THREADS 16

typedef struct{
        char* str;
        char c1;
        char c2;
    } kek;

void replace_char(char* src, char c1, char c2){
    int i = 0;
    while(src[i] != '\0'){
		if(src[i]==c1){
		   src[i]=c2;
	    }
        i++;
    }
}

void reverse(char *src, char* res, int len){
    int i;
    int end = len-1;
    for (i = 0; i < len; i++) {
        res[i] = src[end];
        end--;
    }
    src[i] = '\0';
}

char* replace_reverse(char* src, char c1, char c2){
    char* res = malloc(100 * sizeof(char));
    strcpy(res,src);
    int i = 0;
    while (res[i] != '\0'){
        i++;
    }
    reverse(src, res, i);
    replace_char(res, c1, c2);
    return res;
}

int main(int argc, char* argv[]){
    /* exercice 1*/
    long n = 15;
    long *p = &n;
    long **pp = &p;
    printf("ex1: n=%ld, p=%ld, pp=%ld\n\n",n, *p, **pp);

    /* exercice 2*/
    kek k;
    k.str = malloc(100 * sizeof(char));
    strcpy(k.str, "dior homme");
    k.c1 = ' ';
    k.c2 = '-';
    //replace_char(k.str,k.c1, k.c2);
    //printf("ex2: %s\n\n",k.str);    
    
    /* exercice 3*/
    char* res = replace_reverse(k.str,k.c1,k.c2);
    printf("ex3: %s\n\n",res);    
    
    /* exercice 4 */
    if(argc != 5){
        return EXIT_FAILURE;
    } else {
        printf("%s:\n",argv[1]);
        double src = atof(argv[3]);
        int p = atoi(argv[4]);
        for(int i = 0; i < atoi(argv[2]); i++){
            double res = pow(src,p);
            printf("%.6f^%d = %.6f\n", src, p, res);
            p++;
        }
    }

    free(res);
    free(k.str);

    return 0;
}