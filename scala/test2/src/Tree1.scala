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
  case Empty
  case Leaf( value: Int )
  case Node( left: Tree, right: Tree )

  /*
   * Retourne le nombre de feuilles de l'arbre
   * (en excluant les noeuds intermédiaires).
   */
  /*def size: Int = this match {
    case Empty => 0
    case Leaf(_) => 1
    case Node( l, r ) => l.size + r.size 
  }*/

  enum Todo {
    case Done
    case SubTree( t: Tree, rest: Todo )
  }
  
  def size: Int = {
    import Todo._
    def loop( todo: Todo, res: Int ): Int = todo match {
      case Done => res
      case SubTree( Empty, rest ) => loop(rest, res)
      case SubTree( Leaf(_), rest ) => loop( rest, res+1 )
      case SubTree( Node(l,r), rest) =>
        loop( SubTree( l, SubTree(r, rest ) ), res )
    }
    loop(SubTree(this,Done), 0 )
  }

  /*
   * Returne la profondeur de l'arbre: la longueur du plus long chemin entre la
   * racine et une des feuilles.
   * Un arbre vide a une profondeur de 0, une feuille une profondeur de 1,
   * un noeud avec deux feuilles a une profondeur de 2, etc.
   */
   def depth: Int = this match {
      case Empty => 0
      case Leaf(_) => 1
      case Node( l, r ) => {
        val ld = l.depth
        val rd = r.depth
        1 + ( if( ld > rd ) ld else rd )
      } 
   }

  /*
   * Join deux arbres binaires en créant un nouveau noeud si nécéssaire.
   * 'this' devient la branche de gauche et 'that' la branche de droite.
   * ATTENTION: un noeud ne peut pas contenir un arbre vide (cf. tests)
   */
  def join( that: Tree ): Tree = (this, that) match {
    case ( Empty, _ ) => that
    case ( _, Empty ) => this
    case ( l, r ) => Node( l, r )

  }
/*
 * Opère une rotation à droite: le premier noeud à gauche devient la
 * nouvelle racine.
 *
 *      /  \                      /  \
 *     / \  3  .rotateRight ->   1  / \
 *    1   2                        2   3
 * Si l'opération est impossible, l'arbre est retourné tel quel
 */
  def rotateRight: Tree = this match {
    case Node( Node( ll, lr ), r ) => Node( ll, lr.join(r) )
    case _ => this
  }

  /*
   * Retourne vrai si au moins une des feuille de l'arbre
   * contient l'élément 'i'.
   */
  def contains( i: Int ): Boolean = this match {
    case Leaf( j ) => i == j
    case Empty => false
    case Node( l, r ) => l.contains( i ) || r.contains( i )

  }

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
    case Leaf( j ) if j != i  => this
    case Leaf( _ ) | Empty => Empty
    case Node( l , r ) => l.remove( i ).join( r.remove( i ) )
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
  def single( i: Int ): Tree = Leaf( i )
}