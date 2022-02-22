#include <stdio.h>
#include <stdlib.h>

void main() {
    int montant = 0;
    int count100 = 0;
    int count20 = 0;
    int count10 = 0;
    int configuration = 0;
    printf("Entrez un montant multiple de 10: ");
    scanf("%d",&montant);

    count100 = montant / 100; // nombre de billets de 100
    montant = montant % 100; // reste a distribuer

    count20 = montant / 20; // nombre de billets de 20
    montant = montant % 20; // reste a distribuer

    count10 = montant / 10; // superieur à 1 = probleme
    montant = montant % 10; // il devrait pas il y avoir de reste

    if(montant != 0){
      printf("saisir un montant valide svp c'est la merde on a plus de pieces\n");
      exit(0);
    }
    configuration++; // configuration optimale (banque)

    for (int i = count100; i > 0; i--) {
      count100 -= 1;
      count20 += 5;
      configuration++;
      //printf("configuration : %d\n",configuration);
      for (int j = count20; j > 0; j--) {
        count20 -= 1,
        count10 += 2;
        configuration++;
      }
    }

    for (int j = count20; j > 0; j--) {
      count20 -= 1,
      count10 += 2;
      configuration++;
    }
    printf("nombre de configurations : %d\n", configuration);
}