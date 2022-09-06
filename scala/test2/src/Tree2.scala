package ch.hepia.scala.eval2


 /* Représente un arbre binaire avec les contraintes suivantes:
  *   - structure de données immutable
  *   - les valeurs sont des nombres entiers dans les feuilles
  *   - pas de valeurs dans les noeuds
  *   - L'arbre peut être vide
  *   - Un noeud ne peut pas contenir d'arbre vide
  */
enum Tree {
  /* Remplacer par une meilleure representation */
  enum NETree {
    case Leaf( value: Int )
    case Node( left: NETree, right: NETree )
    
    def size: Int = this match {
      case Leaf( _ ) => 1
      case Node( l, r ) => l.size + r.size
    }

    def remove( i : Int ): Tree = this match {
      case Leaf( j ) if i == j => Empty
      case Leaf( _ ) => NonEmpty(this)
      case Node( l, r ) => 
    }

  }

  case Empty
  case NonEmpty( net: NETree )

  /*
   * Retourne le nombre de feuilles de l'arbre
   * (en excluant les noeuds intermédiaires).
   */
  def size: Int = this match {
    case Empty => 0
    case NonEmpty( net ) => net.size 
  }

  /*
   * Returne la profondeur de l'arbre: la longueur du plus long chemin entre la
   * racine et une des feuilles.
   * Un arbre vide a une profondeur de 0, une feuille une profondeur de 1,
   * un noeud avec deux feuilles a une profondeur de 2, etc.
   */
   def depth: Int = 0

  /*
   * Join deux arbres binaires en créant un nouveau noeud si nécéssaire.
   * 'this' devient la branche de gauche et 'that' la branche de droite.
   * ATTENTION: un noeud ne peut pas contenir un arbre vide (cf. tests)
   */
  def join( that: Tree ): Empty
/*
 * Opère une rotation à droite: le premier noeud à gauche devient la
 * nouvelle racine.
 *
 *      /  \                      /  \
 *     / \  3  .rotateRight ->   1  / \
 *    1   2                        2   3
 * Si l'opération est impossible, l'arbre est retourné tel quel
 */
  def rotateRight: Tree = Empty

  /*
   * Retourne vrai si au moins une des feuille de l'arbre
   * contient l'élément 'i'.
   */
  def contains( i: Int ): Boolean = false
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
   */
  def remove( i: Int ):Tree = this match {
    case Empty => Empty
    case NonEmpty( net ) net.remove( i )
  }
}

object Tree {
  /*
   * Crée un arbre vide
   */
  def empty: Tree = Empty
  /*
   * Crée un arbre avec un seul élément: une feulle.
   */
  def single( i: Int ): Tree = NonEmpty( Leaf( i ) )
}