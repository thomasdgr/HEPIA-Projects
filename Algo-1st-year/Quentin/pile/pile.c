#include "pile.h"

void pile_print(pile stack)
{
    printf("#######\n");
  for(int i=stack.sommet; i>=0;i--)
  {

    printf("%d\n",stack.tab[i]);
  }
    printf("#######\n");
}
pile pile_create(int taille)
{
  pile newPile;
  newPile.sommet=-1;
  newPile.capacite=taille;
  newPile.tab= malloc(taille*sizeof(int));
  return newPile;
}
int pile_destroy(pile *stack){
  free(stack->tab);
}
bool pile_est_vide(pile stack)
{
  return stack.sommet==-1;
}
bool pile_est_pleine(pile stack)
{
  return stack.sommet==stack.capacite-1;
}
int pile_empiler(pile *stack, int nombre)
{
  if(stack->sommet<stack->capacite)
  {

    stack->sommet+=1;
    stack->tab[stack->sommet]= nombre;
    return 1;
  }else
  {
    return 0;
  }
}
int pile_depiler(pile *stack, int nombre){
  for(int i=0; i<=stack->sommet;i++)
  {
    if(nombre==stack->tab[i])
    {
      for(int j=i;j<=stack->sommet-1;j++)
      {
        stack->tab[j]=stack->tab[j+1];
      }
      stack->sommet-=1;
      break;
    }
  }
}
int pile_transfert(pile *stackGauche, pile *stackDroite, int nombre, int cas)
{
  for(int i=0; i<=stackGauche->sommet;i++)
  {
    if(nombre>stackGauche->tab[i] && cas==0)
    {
      pile_empiler(stackDroite, stackGauche->tab[i]);
      pile_depiler(stackGauche, stackGauche->tab[i]);
    }
    if(nombre<=stackGauche->tab[i] && cas==1)
    {
      pile_empiler(stackDroite, stackGauche->tab[i]);
      pile_depiler(stackGauche, stackGauche->tab[i]);
    }

  }
}
int pile_transvasement(pile *stackGauche, pile *stackDroite)
{
  for(int i=stackDroite->sommet;i>=0;i--)
  {
    pile_empiler(stackGauche, stackDroite->tab[i]);
    pile_depiler(stackDroite, stackDroite->tab[i]);
  }


}
int pile_step(pile *stackGauche, pile *stackDroite, int nombre)
{

      pile_transfert(stackGauche, stackDroite,nombre,0);
      pile_transfert(stackDroite, stackGauche,nombre,1);
      pile_empiler(stackGauche,nombre);
  }

int pile_tri_complet(pile *stackGauche, pile *stackDroite,int *tableau, int tailleTableau)
{

  for(int i=0; i<tailleTableau;i++)
  {
    pile_step(stackGauche,stackDroite,tableau[i]);
  }
  pile_transvasement(stackGauche,stackDroite);

}
