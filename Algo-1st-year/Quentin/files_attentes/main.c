#include "queue_array_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
  queue file = queue_creer(6);
  for(int i=0; i<6;i++){
    queue_inserer(&file,i+2);
  }
  queue_print(file);
  queue_extraire(&file);
  queue_print(file);

}
