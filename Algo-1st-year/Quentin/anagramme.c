#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void main()
{
 char mot1[]= "chien";
 char mot2[]= "niche";
 char lettreReference;
 int tailleMot1=strlen(mot1);
 int tailleMot2=strlen(mot2);
 char caractereTemporaire;
 bool identique=true;

 //Tri du deuxième mot pour qu'il soit identique au premier
 if(tailleMot1==tailleMot2)
 {


   for(int j=0;j<tailleMot1;j++)
   {
     lettreReference=mot1[j];
     for(int i=j; i<tailleMot1;i++)
     {
       if(mot2[i]==lettreReference)
       {
         caractereTemporaire=mot2[j];
         mot2[j]=mot2[i];
         mot2[i]=caractereTemporaire;
         break;
       }
     }
     //printf("Tableau2 donnees: %s\n",mot2);
   }
   //Comparaison si les deux mots sont identiques
   for(int k=0; k<tailleMot1;k++)
   {
     if(mot1[k]!=mot2[k])
     {
       identique=false;
       break;
     }
   }
}
else{
  identique=false;
}

   printf("Tableau1 donnees: %s\n",mot1);
   printf("Tableau2 donnees: %s\n",mot2);
   if(identique)
   {
     printf("Les mots sont des anagrammes.\n");
   }
   else{
     printf("Les mots ne sont pas des anagrammes\n");
   }


}
