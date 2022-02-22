#include <stdio.h>
#include <stdlib.h>
#include "circular_list.h"

void joseph_insert(anneau* ring,int n) {
   for (int i=1;i<=n;i++) {
      insert(ring,i);
   }
}

void joseph_extract(anneau* ring,int k) {
   while(!is_empty(*ring))
   {
      move(ring,k-1);
      printf("%d ",extract(ring));
   }
   printf("\n");
}

int main(int argc,char** argv) {
    argc++;
   anneau ring = init();
   int n = atoi(argv[1]);
   int k = atoi(argv[2]);
   joseph_insert(&ring,n);
   println(ring);
   joseph_extract(&ring,k);
   return 0;
}
