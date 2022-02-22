#include "pile.h"
int main()
{
  int tableau[]={17,34,20,40,25};
  pile pileGauche=pile_create(5);
  pile pileDroite=pile_create(5);
  //printf("Est vide 1:%d 2:%d",(int) pile_est_vide(pileGauche),(int)pile_est_pleine(pileDroite));
/*  pile_empiler(&pileGauche,tableau[0]);
  pile_empiler(&pileGauche,tableau[1]);
  pile_empiler(&pileGauche,tableau[2]);
  pile_print(pileGauche);
  printf("Sommet:%d\n", pileGauche.sommet);
  pile_depiler(&pileGauche,20);
  pile_print(pileGauche);
  printf("Sommet:%d\n", pileGauche.sommet);*/
  pile_tri_complet(&pileGauche,&pileDroite,tableau,5);

  pile_print(pileGauche);
  pile_print(pileDroite);
}
