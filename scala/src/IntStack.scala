package ch.hepia.tp

/*
 * Représente une pile d'entiers
 */
enum IntStack {
    case Elem( top: Int, rest: IntStack )
    case Empty

    /*
     * Retourne vrai ssi la pile est vide
     */
    def isEmpty = this match {
        case Elem(_,_) => false
        case Empty => true
    }

    /*
     * Retourne la taille de la pile.
     * A IMPLEMENTER
     */
    def size: Int = this match {
        case Elem(_,r) => 1 + r.size
        case Empty => 0 
    }

    def size2: Int = {
        def loop(n: Int, cur: IntStack): Int =
            if(cur.isEmpty) n else {
                var Elem(_,r) = cur
                loop(n+1,r)
            }

        loop(0,this)
    }

    /*
     * Ajoute un élément au sommet de la pile
     * A IMPLEMENTER
     */
    def push( i: Int ): IntStack = Elem(i, this)

    /*
     * Retire et retourne l'élément au sommet de la pile.
     * Si la pile est vide, cause une exception (moche).
     * A IMPLEMENTER
     */
    def pop: (Int,IntStack) = this match {
        case Empty => throw new NoSuchElementException("Empty stack")
        case Elem(t,r) => (t,r)
    }
    
    /*
     * Prend l'élément du sommet de la pile et
     * le place en bas de la pile. Si la pile est
     * vide, ne fait rien.
     * A IMPLEMENTER
     */
    def rotate: IntStack = this match {
        case Empty => Empty
        case Elem(top,rest) => Empty.push(top).pushAll(rest)
    }

    /*
     * Retourne l'élément tout en bas de la pile (sans le supprimer).
     * Si la pile est vide, lève une exception.
     * A IMPLEMENTER
     */
    @annotation.tailrec
    final def bottom: Int = this match {
        case Empty => throw new NoSuchElementException("Empty stack")
        case Elem(i, Empty) => i
        case Elem(_, r) => r.bottom
    }

    private def revAdd(from: IntStack, to: IntStack): IntStack = from match {
        case Empty => to
        case Elem(i, rest) => revAdd(rest, to.push(i))
    }
  
    /*
     * Renverse des éléments de la pile. Si la pile est vide,
     * ne fait rien.
     * A IMPLEMENTER
     */
    def reverse: IntStack = revAdd(this, Empty)

    /*
     * Place tous les éléments de la pile 'that' au sommet de la pile
     * actuelle.
     * A IMPLEMENTER
     */
    def pushAll(that: IntStack): IntStack = revAdd(that.reverse, this)
}
