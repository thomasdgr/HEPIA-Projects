#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int taille_chaine(char* mot){
  int cpr=0;
  while(mot[cpr]!='\0'){
    cpr++;
  }
  return cpr;
}
int nombre_caracteres(char* mot, char c){
  int tailleMot=taille_chaine(mot);
  int nblettre=0;
  for(int i=0; i<tailleMot;i++){
    if(mot[i]== c){
      nblettre++;
    }
  }
  return nblettre;
}
bool lettre_check(char* mot1, char *mot2, char c){
  int tailleMot1=taille_chaine(mot1);
  int tailleMot2= taille_chaine(mot2);
  return nombre_caracteres(mot1, c)==nombre_caracteres(mot2, c);

}
int main(){
  char *mot1="fariner";
  char *mot2="refrain";
  int tailleMot1=taille_chaine(mot1);
  int tailleMot2= taille_chaine(mot2);
  bool estUnAnagramme=true;
  if(tailleMot1==tailleMot2){
    for(int i=0; i<tailleMot1;i++){
      if(!lettre_check(mot1,mot2,mot1[i])){
        estUnAnagramme=false;
      }
    }
  }else{
    estUnAnagramme=false;
  }


  printf("%d",estUnAnagramme);

}
