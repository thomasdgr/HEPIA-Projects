package ch.hepia.tp

//Ensemble d'éléments de type T
case class ISet[T]( contains: T=>Boolean ) {
  /* Ajoute un seul élément à l'ensemble.
   * A IMPLEMENTER
   */
  def add( elem: T ): ISet[T] = this.union(ISet.single(elem))
  //def add( elem: T ): ISet[T] = ISet[T]( t => this.contains(t) || t == elem )
  
  /* Union d'ensembles.
   * A IMPLEMENTER
   */
  def union( that: ISet[T] ): ISet[T] = ISet[T]( t => this.contains(t) || that.contains(t))
  
  /* Intersection d'ensembles.
   * A IMPLEMENTER
   */
  def intersection( that: ISet[T] ): ISet[T] = ISet[T]( t => this.contains(t) && that.contains(t))
  
  /* Différence d'ensembles
   * A IMPLEMENTER
   */
  def difference( that: ISet[T] ): ISet[T] = ISet[T]( t => this.contains(t) && !that.contains(t))
}

// De base, on a une classe ISet[T] avec un lambda T => Boolean
//    -> pour un empty on a "_ => false": (pour tous t, retourne un ensemble vide)
//    -> pour un single on a "t => condition_booleene": (sachant t, retourne un ensemble contenant el quand el=t)

// pour toutes les fonctions, on doit retourner un ensemble qui satisfait le "lambda t => Boolean"
// ce lambda, on peut le modifier tant qu'on a un t à gauche et une condition booleenne à droite

// pour le add, on retourne un ensemble de t 
// quand t satisfait la condition "est déjà dans la liste" ou "est égal à l'élément à ajouter"

// pour l'union, on retourne un ensemble de t
// quand t satisfait la condition "est dans la liste initiale" OU "est dans la liste donnée en argument"

// pour l'intersection, on retourne un ensemble de t
// quand t satisfait la condition "est dans la liste initiale" ET "est dans la liste donnée en argument"

// pour la différence, on retourne un ensemble de t
// quand t satisfait la condition "est dans la liste initiale" ET "n'est pas dans la liste donnée en argument"

object ISet {
  /* Crée un ensemble vide.
   */
  def empty[T] = ISet[T]( _ => false )

  /* Crée un ensemble avec un seul élément
   * A IMPLEMENTER
   */
  def single[T]( elem: T ) = ISet[T]( t => t == elem )
}