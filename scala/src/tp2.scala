package ch.hepia.tp

def dumbCount1( n: Int ): Int =
  if( n == 0 ) 0 else 1 + dumbCount1(n-1)
// ca va juste nous retourner notre nombre
// si on test avec n = 1'000'000 -> cette fonction plante
// si on test avec un nombre négatif ça marche pas
// => on a une erreur de StackOverflow
//    dans cette fonction on doit se souvenir de tous les états pour pouvoir retourner
//    donc si on a trop d'ittérations on pète la pile et ça plante

def dumbCount2( n: Int ): Int = {
  def dumby( m: Int, c: Int ): Int =
    if( m == 0) c else dumby(m-1,c+1)
  dumby( n, 0 )
}
// ca va juste nous retourner notre nombre
// si on test avec n = 1'000'000 -> cette fois-ci ça marche

@main
// def tp2( n: Int, s: String, b:Boolean ) = { <- exemple d'arguments pour le main
def tp2( n: Int ) = {
  println( dumbCount1( n ) )
  //println( dumbCount2( n ) )
}

/*
on pose dumbCount1() = f():
f(3)
= if(3==0) 0 else 1 + f(3-1)
= if(false) 0 else 1 + f(3-1)
= 1 + f(3-1)
= 1 + f(2)
= 1 + ( if(2==0) 0 else 1 + f(2-1) )
= 1 + ( if(false) 0 else 1 + f(2-1) )
= 1 + ( 1 + f(2-1) )
= 1 + ( 1 + f(1) )
= 1 + ( 1 + ( if(1==0) 0 else 1 + f(1-1) ) )
= 1 + ( 1 + ( if(false) 0 else 1 + f(1-1) ) )
= 1 + ( 1 + ( 1 + f(1-1) ) ) )
= 1 + ( 1 + ( 1 + f(0) ) ) )
= 1 + ( 1 + ( 1 +  ( if(0==0) 0 else 1 + f(0-1) ) ) )
= 1 + ( 1 + ( 1 +  0 ) )
= 3

g(3, 0)
if(3==0) 0 else g(3-1, 0+1)
g(3-1, 0+1)
g(2, 1)
if(2==0) 0 else g(2-1, 1+1)
g(2-1, 1+1)
g(1, 2)
if(1==0) 0 else g(1-1, 2+1)
g(1-1, 2+1)
g(0, 3)
if(0==0) 0 else g(0-1, 3+1)
0

avec la seconde fonction, on a beaucoup moins d'étapes pour la même chose
-> ce qui explique donc pourquoi, avec la première fonction on dépasse de la pile mais pas la seconde
*/