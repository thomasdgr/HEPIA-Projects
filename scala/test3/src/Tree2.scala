package ch.hepia.scala.eval3



/*
 * Représente un arbre binaire avec les contraintes suivantes:
 *   - structure de données immutable
 *   - les valeurs sont des nombres entiers dans les feuilles
 *   - pas de valeurs dans les noeuds
 *   - L'arbre peut être vide
 *   - Un noeud ne peut pas contenir d'arbre vide
 * */
enum Tree[+T] {
  /* Proposer une représentation */
  case Leaf( value: T )
  case Node( left: Tree[T], right: Tree[T] )
  case Empty

  /*
   * Join deux arbres binaires en créant un nouveau noeud si nécéssaire.
   * 'this' devient la branche de gauche et 'that' la branche de droite.
   * ATTENTION: un noeud ne peut pas contenir un arbre vide (cf. tests)
   */
  def join[S >: T]( that: Tree[S] ): Tree[S] = (this,that) match {
    case (Empty,r) => r
    case (l,Empty) => l
    case (l,r) => Node(l,r)
  }


  /* La fonction map applique une fonction sur chaque valeur
   * et retourne un arbre de même structure, contenant les
   * valeurs produites:
   *
   *      /  \                      /  \
   *     / \  3  .map( _ * 2 ) ->  2  / \
   *    1   2                        4   6
   */

  def map[U]( f: T=>U ): Tree[U] = this match {
    case Leaf(v) => Leaf(f(v))
    case Node(l,r) => Empty.join(l.map(f)).join(r.map(f))
    case Empty => Empty
  }

  /*
   * La foncton filter garde uniquement les valeurs
   * pour lesquels la fonction passée en argumnt est
   * vraie
   *
   *      /  \                          /  \
   *     / \  3  .filter( _%2==1 ) ->  1    3
   *    1   2
   */
  def filter( f: T=>Boolean ): Tree[T] =  this match {
    case Empty => Empty
    case Leaf(v) if(f(v)) => Leaf(v)
    case Leaf(_) => Empty
    case Node(l,r) => Empty.join(l.filter(f)).join(r.filter(f))
  } 

  /*
   * La fonction reduce permet de réduire un arbre
   * en une seule valeur en appliquant une fonction
   * binaire entre les feuilles. L'argument 'e' est
   * retourné si l'arbre est vide.
   *
   *      /  \
   *     / \  3  .reduce( 0, _ + _ )  -> 6
   *    1   2
   */
  def reduce[U >: T]( e: U, g:(U,U)=>U ): U = this match {
    case Empty => e
    case Leaf(v) => v
    case Node(l,r) => g(l.reduce(e,g), r.reduce(e,g))
  }

   /*
   * Retourne le nombre de feuilles de l'arbre
   * (en excluant les noeuds intermédiaires).
   * ATTENTION:
   *  - Pas de pattern matching
   *  - Utiliser les fonctions map et reduce
   */
  def size: Int = 
    this.map( v => 1 )
        .reduce( 0, ( v, w ) => v + w )

  /*
   * Retourne vrai si au moins une des feuille de l'arbre
   * contient l'élément 'i'.
   * ATTENTION:
   *  - Pas de pattern matching
   *  - Utiliser les fonctions map et reduce
    */
  def contains[U >: T]( u: U ): Boolean = 
    this.map( v => v == u )
        .reduce( false, ( v, w ) => v || w )

  /*
   * Supprime toutes les occurences de 'i' parmis les
   * feuilles de l'arbre. Si l'élément n'apparait pas,
   * l'arbre est retourné tel quel.
   * La structure de l'arbre doit être préservée au mieux.
   *
   *   /    \                     / \
   *  / \  / \  .remove(1) ->    2   3
   * 1  2  3  1
   *
   * ATTENTION:
   *  - Pas de pattern matching
   *  - Utiliser la fonction filter
    */
   def remove[U >: T]( u: U ):Tree[T] = this.filter( v => v != u )
}

object Tree {
  /*
   * Crée un arbre vide
   */
  def empty = Empty
  /*
   * Crée un arbre avec un seul élément: une feulle.
   */
  def single[T]( t: T ): Tree[T] = Leaf(t)

}