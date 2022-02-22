#ifndef _CIRCULAR_LIST_H_
#define _CIRCULAR_LIST_H_
#include <stdbool.h>

typedef struct _element {
   int info;
   struct _element* suivant;
} element;

typedef element* anneau;

// initialise un anneau à NULL
anneau init();
// retourne vrai si l'anneau est NULL, faux sinon
bool is_empty(anneau ring);
// insère après l'élément pointé par *ring
void insert(anneau* ring,int val);
// décale *ring k-fois
void move(anneau* ring,int k);
// si val est dans l'anneau, place *ring sur l'élément
// avant celui contenant val et retourne vrai,
// sinon ne fait rien et retourne faux
bool search(anneau* ring,int val);
// supprime l'élément suivant l'élément pointé par *ring
int extract(anneau* ring);
// si val est dans l'anneau, place *ring sur l'élément
// avant celui contenant val et supprime cet élément,
// sinon ne fait rien
void delete(anneau* ring,int val);
// imprime l'anneau
void println(anneau ring);

bool ispresent(anneau annu, int val);

#endif
