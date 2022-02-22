#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _fraction {
   int num;
   int den;
} fraction;

void print(fraction frac) {
   printf(" %d/%d ",frac.num,frac.den); 
}

int pgcd(int n,int m) {
   assert(n > 0 && m > 0);
   int tmp_n = n,tmp_m = m;
   while (tmp_n%tmp_m > 0) {
      int tmp = tmp_n;
      tmp_n = tmp_m;
      tmp_m = tmp%tmp_m;
   }
   return tmp_m;
}

void reduire(fraction* frac) {
   if (0 == frac->num) { 
      frac->den = 1;
   } else {
      int gcd = pgcd(abs(frac->num),frac->den);
      frac->num /= gcd;
      frac->den /= gcd;
   }
}

fraction fraction_build(int num,int den) {
   assert(den != 0);
   int sign = den/abs(den);
   fraction res = {sign*num,sign*den};
   reduire(&res);
   return res;
}

fraction add(fraction frac1,fraction frac2) {
   return fraction_build(frac1.num*frac2.den+frac1.den*frac2.num,frac1.den*frac2.den);
}

fraction add1(int n,fraction frac) {
   return add(fraction_build(n,1),frac);
}

fraction add2(fraction frac,int n) {
   return add1(n,frac);
}

void add_inplace(fraction* frac1,fraction frac2) {
   *frac1 = add(*frac1,frac2);
}

fraction sub(fraction frac1,fraction frac2) {
   return add(frac1,fraction_build(-frac2.num,frac2.den));
}

fraction sub1(int n,fraction frac) {
   return sub(fraction_build(n,1),frac);
}

fraction sub2(fraction frac,int n) {
   return sub1(n,frac);
}

void sub_inplace(fraction* frac1,fraction frac2) {
   *frac1 = sub(*frac1,frac2);
}

fraction mult(fraction frac1,fraction frac2) {
   return fraction_build(frac1.num*frac2.num,frac1.den*frac2.den);
}

fraction mult1(int n,fraction frac) {
   return mult(fraction_build(n,1),frac);

}

fraction mult2(fraction frac,int n) {
    return mult1(n,frac);
}

void mult_inplace(fraction* frac1,fraction frac2) {
   *frac1 = mult(*frac1,frac2);
}

fraction divide(fraction frac1,fraction frac2) {
   assert(frac2.num != 0);
   int sign = frac2.num/abs(frac2.num);
   return mult(frac1,fraction_build(sign*frac2.den,abs(frac2.num)));
}

fraction div1(int n,fraction frac) {
      return divide(fraction_build(n,1),frac);


fraction div2(fraction frac,int n) {
       return div1(n,frac);

}

void divide_inplace(fraction* frac1,fraction frac2) {
   *frac1 = divide(*frac1,frac2);
}

fraction puiss(fraction frac,int n) {
   fraction prod = fraction_build(1,1); 
   for (int i=1;i<=abs(n);i++) {
      prod = mult(prod,frac);
   }
   if (n < 0) {
      prod = div1(1,prod);
   }
   return prod;
}

float reel(fraction frac) {
   return (float)frac.num/(float)frac.den;
}

fraction compute(fraction f1,fraction f2,char op) {     
   fraction res;
   switch(op) {
      case 'x': res = mult(f1,f2);      break;     
      case '+': res = add(f1,f2);       break;       
      case '/': res = divide(f1,f2);    break;      
      case '-': res = sub(f1,f2);       break;
      case 'p': res = puiss(f1,f2.num); break;
      default : printf("Pas implémenté\n");
   }
   return res;
}
  
void main(int argc,char** argv) {
   fraction f1,f2;
   switch(argc) {
      case 3:
         printf("%d\n",pgcd(atoi(argv[1]),atoi(argv[2])));
         break;
      case 5:
         // teste si le 2ème argument est un dénominateur (donc > 0)
         if ('1' <= argv[2][0] && argv[2][0] <= '9') {
            f1 = fraction_build(atoi(argv[1]),atoi(argv[2]));
            f2 = fraction_build(atoi(argv[4]),1);
            print(compute(f1,f2,argv[3][0]));
         } else {
            f1 = fraction_build(atoi(argv[1]),1);
            f2 = fraction_build(atoi(argv[3]),atoi(argv[4]));
            print(compute(f1,f2,argv[2][0]));
         }
         break;
      case 6:
         f1 = fraction_build(atoi(argv[1]),atoi(argv[2]));
         print(f1); printf("\n");
         f2 = fraction_build(atoi(argv[4]),atoi(argv[5]));
         print(f2); printf("\n");
         print(compute(f1,f2,argv[3][0]));
         break;
      default: printf("Pas implémenté\n");
   }
   printf("\n");
}


