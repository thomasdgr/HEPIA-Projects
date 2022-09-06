package ch.hepia.tp

def fac2( n: Long ): Long = {
  def fak(n1: Long, n2: Long): Long = 
    if( n2 == 0 ) n1 else fak(n1 * n2, n2 - 1)
  fak(n, n-1)
}

def gcd2( a: Int, b: Int ): Int =
  if( b == 0 ) a
  else gcd( b, a%b )

def syracuse(n: Int): Int = {
    if (n == 1) 0 else {
        1 + syracuse(if( n%2 == 0 ) n/2 else 3*n+1)
    }
}

def syracuse2(n: Int): Int = {
    def rec(n: Int, c: Int): Int =
        if( n == 1) c
        else if( n%2 == 0 ) rec(n/2, c+1)
        else rec(3*n+1, c+1)
    rec(n,0)
}

@main
def tp2b = {
  println( s"  Fonction fac: ${fac2(8) == 40320}" )
  println( s"  Fonction gcd: ${gcd2(1071, 462) == 21}" )
  println( s"  syracuse: ${syracuse(14)}" )
  println( s"  syracuse v2: ${syracuse2(14)}" )
}
