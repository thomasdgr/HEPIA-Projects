#include"pile_array_int.h"
#include <stdio.h>

void step(pile *pileGauche, pile *pileDroite,int val){

  int compteur=pileGauche->sommet;
  while(pileGauche->data[compteur]<val && !pile_est_vide(*pileGauche)){
      int valeurSommet= pile_depiler(pileGauche);
      pile_empiler(pileDroite,valeurSommet);
      compteur=pileGauche->sommet;
    }
    compteur=pileDroite->sommet;
    while(pileDroite->data[compteur]>val && !pile_est_vide(*pileDroite)){
        int valeurSommet= pile_depiler(pileDroite);
        pile_empiler(pileGauche,valeurSommet);
        compteur=pileDroite->sommet;
      }

    pile_empiler(pileGauche,val);

}
void transvasement(pile *pileGauche, pile *pileDroite){
  while(pileDroite->sommet!=-1){
    int valeurSommet= pile_depiler(pileDroite);
    pile_empiler(pileGauche,valeurSommet);
  }
}
void pile_print(pile stack)
{
    printf("#######\n");
  for(int i=0; i<=stack.sommet;i++)
  {

    printf("%d ",stack.data[i]);
  }
    printf("\n#######\n");
}
int main()
{
  int tableau[]={17,34,20,40,25};
  pile pileGauche=pile_creer(5);
  pile pileDroite=pile_creer(5);
  for(int i=0;i<5;i++){
    step(&pileGauche,&pileDroite,tableau[i]);
  }
  transvasement(&pileGauche,&pileDroite);
  //printf("Est vide 1:%d 2:%d",(int) pile_est_vide(pileGauche),(int)pile_est_pleine(pileDroite));
/*  pile_empiler(&pileGauche,tableau[0]);
  pile_empiler(&pileGauche,tableau[1]);
  pile_empiler(&pileGauche,tableau[2]);
  pile_print(pileGauche);
  printf("Sommet:%d\n", pileGauche.sommet);
  pile_depiler(&pileGauche,20);
  pile_print(pileGauche);
  printf("Sommet:%d\n", pileGauche.sommet);*/


  pile_print(pileGauche);
  pile_print(pileDroite);
}
