#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

typedef enum _mois {jan=1,feb,mar,apr,may,jun,jul,aug,sep,oct,nov,dec} mois; 

typedef struct _date {
   int day;
   mois mo;
   int an;
} date;

bool date_valid(date dt) {
   if(0 > dt.day){
      return false;
   }
   switch(dt.mo) {
      case feb: if(dt.day > 29){
         return false; 
      } 
      case apr: ;
      case jun: ;
      case sep: ;
      case nov: if(dt.day > 31){
         return false;
      }
      default: if(dt.day > 31){
         return false;
      }
   }
   return true;
}

void main() {
   int jour = 0;
   mois mois;
   int annee = 0;
   printf("Entrez un jour (0-31): ");
   scanf("%d",&jour);
   printf("Entrez un mois avec trois lettres (jan-dec): ");
   scanf("%s",&mois);
   printf("Entrez une année: ");
   scanf("%d",&annee);
   date dt = {jour,mois,annee};
   if(date_valid(dt)){
      printf("La date est valide\n ");
   } else {
      printf("La date n'est pas valide\n ");
   }

}

