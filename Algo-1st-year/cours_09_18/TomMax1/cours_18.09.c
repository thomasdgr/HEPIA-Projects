#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void main() {
    int nb1 = 0;
    int nb2 = 0;
    int size = 0;
    printf("Entrez un nombre: ");
    scanf("%d",&nb1);
    nb_premier(nb1);
    factorielle(nb1);
    binaire(nb1);
    printf("\nEntrez un second nombre: ");
    scanf("%d",&nb2);
    ppcm(nb1,nb2);
    pgcd(nb1,nb2, "euclide");
    printf ("\nEntrez un nombre pour la suite de Fibonacci: ");
    scanf ("%d", &size);
    fibonacci(size);
    printf ("Crible d'Eratosthene : ");
    crible(size);

}

int nb_premier(int nb){
    bool premier = true;
    for (int i = 2; i <= nb; i++) {    // je devrais utiliser sqrt() mais ca marche pas
        if (nb % i == 0) {
            premier = false;
            break;
        }
    }
    if (premier) {
      printf("Le nombre %d est premier\n",nb);
    } else {
      printf("Le nombre %d n'est pas premier\n",nb);
    }
    return 1;
}

int factorielle(int nb){
    int fact = 1;
    for(int i=2;i<=nb;i++) {
        fact *= i;
    } 
    printf("Fact = %d\n",fact);
    return 1;
}

int ppcm(int nb1, int nb2){
    int res = nb1*nb2;
    for (int i = 2; i <= nb2; i++) {
        if (nb1 * i % nb2 == 0) {
            res = nb1 * i;
            break;
        }
    }
    printf("Le ppcm de %d et %d est %d\n",nb1,nb1,res);
    return 1;
}

int pgcd(int nb1, int nb2, char way[10]){
    int tmp_n = nb1;    
    int tmp_m = nb2;
    int pgcd = 0;
    if(way == "naif"){
        // algorithme naif
        for (int div = nb1; div >= 2; div--) {
            if (nb1%div == 0 && nb2%div == 0) {
                pgcd = div;
                break;
            }
        }
    }
    if(way == "euclide"){
        // algorithme d'Euclide
        while (tmp_n%tmp_m > 0) {
            int tmp = tmp_n;
            tmp_n = tmp_m;
            tmp_m = tmp%tmp_m;
        }
    } else {
        printf("bad argument for index way in ppcm fuction -> main");
        return 0;
    }
    printf("Le pgcd de %d et %d est %d\n",nb1,nb2,tmp_m);
    return 1;
}

int crible(int size){
    bool tab[size];
    for (int i=0;i<size;i++) tab[i] = true;  

    for (int i=2;i<size;i++) {
        if (tab[i]) {
            int j = i;
            while (true) {
                j += i;
                if (j >= size) {
                    break;
                }
                tab[j] = false;
            } 
        } 
    }
    
    for (int i=2;i<size;i++) 
        if (tab[i]) printf("%d ",i); 
    printf("\n");
}

int fibonacci(int n){
    int i = 0;
    double a = 0;
    double c = 0;
    double b = 1;

    if (n==0 || n==1) {
        printf ("n = %d", n);
    } else {
        for (i=2;i<=n;i++){
            a = b + c;
            c = b;
            b = a;
        }
	}
	printf ("resultat = %lf\n", a);
}

int fib(int n) {
   switch(n) {
    case 0: return 0;
    case 1: return 1;
    default: return fib(n-1)+fib(n-2);
   }
}

int puissance(int a,int b) {
   if (0 == b) {
      return 1;
   } else if (0 == b%2) { 
      return puissance(a,b/2)*puissance(a,b/2);
   } else {
      return puissance(a,b-1)*a;
   }
}

void binaire(int n) {
   if (n/2 != 0) {
      binaire(n/2);
   }
   printf("%d",n%2);
}

