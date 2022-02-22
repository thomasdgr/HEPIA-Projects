#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>


/*type Array_Int; // type tableau d'entiers à 1 dimension
type Pile_Int; // type pile d'entiers

// Retourne "a < b" si <op> = "<", "a >= b" si <op> = ">=", 
// "true" si <op> = "" et "false" sinon
function condition(a,b : Integer; op : String) return Boolean;

// Transfère les éléments de <pile_1> à <pile_2> 
// tant que condition(sommet(pile_1),val,op) est vrai
procedure transfert(pile_1, pile_2 : Pile_Int; 
                    val: Integer; op : String);

// Trie à l'aide de 2 piles
procedure trier(tab : Array_Int)
   pile_g,pile_d : Pile_Int;
begin
   // parcourt le tableau <tab>
   for i in 0..tab.length loop
      // transfère les éléments de <pile_g> à <pile_d> 
      // tant que sommet(pile_g) < tab[i]
      transfert(pile_g,pile_d,tab[i],"<");
      // transfère les éléments de <pile_d> à <pile_g> 
      // tant que sommet(pile_d) >= tab[i]
      transfert(pile_d,pile_g,tab[i],">=");
      // empile l'élément <tab[i]> dans <pile_g>
      empiler(pile_g,tab[i]);
   end loop;

   // transfère tous les éléments de <pile_d> à <pile_g>
   transfert(pile_d,pile_g,0,"");

   // transfère tous les éléments de <pile_g> dans <tab>
   for i in 0..tab.length loop
      depiler(pile_g,tab[i]);
   end loop;      
end Trier;*/


typedef struct pile
{
    int *tab;
    int max;
    int sommet;
} pile;

bool pile_est_vide(pile stack){
    return stack.sommet == -1;
}

bool pile_est_pleine(pile stack){
    if(pile_est_valide(stack)){
        return stack.sommet == stack.max-1;
    }
}

pile pile_create(int capacite){
    pile stack;
    stack.sommet = -1;
    stack.max = capacite;
    stack.tab = malloc(capacite * sizeof(int));
    return stack;
}

bool pile_est_valide(pile stack){
    return (stack.max >= 0 && stack.sommet >= -1);
}

int pile_sommet(pile stack){
    if (!pile_est_vide(stack)){
        return stack.tab[stack.sommet];
    }
}

void pile_destroy(pile *stack){
    stack->max = -1;
    stack->sommet = -40;
    free(stack->tab);
}

void pile_resize(pile *stack, int size){
    if(pile_est_valide(*stack)){
        stack->max = size;
        stack->tab = realloc(stack->tab, size * sizeof(int));
    }
}

void pile_empiler(pile *stack, int val){
    if(pile_est_valide(*stack)){
        if (pile_est_pleine(*stack)){
            pile_resize(stack, stack->max + 1);
        }
        stack->sommet++;
        stack->tab[stack->sommet] = val;
    }
}

int pile_depiler(pile *stack){
    if(pile_est_valide(*stack)){
        int val = pile_sommet(*stack);
        stack->sommet--;
        return val;
    }
}


//////////////////// AVEC LES POINTEURS /////////////////////////

/* Utilité du typedef : Element a; <=> struct Element a; */
typedef struct _element {
   int data;
   struct _element* next;
} element;
typedef element* pile_ptr;

pile_ptr pile_creer_ptr() {
   return NULL;
}

bool pile_est_vide_ptr(pile_ptr stack) {
   return (NULL == stack);
}

void pile_empiler_ptr(pile_ptr* stack,int val) {
   element* elmt = malloc(sizeof(element));
   elmt->data = val;
   elmt->next = *stack;
   *stack = elmt;
}

int pile_sommet_ptr(pile_ptr stack) {
    if(pile_est_vide_ptr(stack)){
        return stack->data;
    }
}

int pile_depiler_ptr(pile_ptr* stack) {
   if(pile_est_valide_ptr(*stack)){
        int data = pile_sommet_ptr(*stack);
        data--;
        return data; 
    }  
}

void pile_detruire_ptr(pile_ptr* stack) {
   while(!pile_est_vide_ptr(stack)){
       int val = pile_depiler_ptr(stack);
   }   
}

int pile_count_ptr(pile_ptr stack) {
   int cnt = 0;
   element *courant = stack;
   while (courant != NULL){
       courant = courant->next;
       cnt++;
   }   
   return cnt;
}