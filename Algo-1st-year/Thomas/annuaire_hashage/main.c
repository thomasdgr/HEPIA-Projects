#include "hachage.h"
#include <string.h>
int main(){
  annuaire annu= annuaire_init(4);
  personne pers1;
  strcpy(pers1.nom,"bia");
  personne pers2;
  strcpy(pers2.nom,"ay");
  personne pers3;
  strcpy(pers3.nom,"mi");
  personne pers4;
  strcpy(pers4.nom,"do");
  annuaire_insert(&annu,pers1);
  personne pers5;
  strcpy(pers5.nom,"no");
  //strcpy(annu.table[0].person.nom,"Quentin");
  //strcpy(annu.table[1].person.nom,"Chacha");
  //strcpy(annu.table[2].person.nom,"Nils");
  annuaire_insert(&annu,pers2);
  annuaire_insert(&annu,pers3);
  annuaire_insert(&annu,pers4);
  //annuaire_insert(&annu,pers5);
  annuaire_remove(&annu,"do");
  annuaire_print(annu);

}
