package ch.hepia.scala.eval3

import org.scalatest.funsuite.AnyFunSuite

class Tree2Suite extends AnyFunSuite {

  import Tree.*

  test("Tree can be mapped" ) {
    val t123 = single(1).join(single(2).join(single(3)))
    assert( Empty.map( _.toString ) == Empty )
    assert( t123.map( x => x ) == t123 )
    assert( t123.map( _.toString ) == single("1").join(single("2").join(single("3"))))
    assert( t123.map( _.toString ).map( _.toInt ) == t123 )
  }
  test("Tree can be filtered" ) {
    val t123 = single(1).join(single(2).join(single(3)))
    assert( (Empty:Tree[Int]).filter( _ > 0 ) == Empty )
    assert( t123.filter( _ > 0 ) == t123 )
    assert( t123.filter( _ > 10 ) == Empty )
    assert( t123.filter( _ % 2 == 1 ) == t123.remove(2) )
    assert( t123.filter( _ % 2 == 0 ) == t123.remove(1).remove(3) )
  }
  test("Tree can be reduced") {
    val t123 = single(1).join(single(2).join(single(3)))
    assert( Empty.reduce( "blah blah", _ + _ ) == "blah blah" )
    assert( t123.reduce( 0, _ + _ ) == (1+2+3) )
    assert( t123.map( _ + 1 ).reduce( 1, _ * _ ) == (2*3*4) )
    assert( t123.map( i => i == 2 ).reduce( false, _ || _ ) == t123.contains(2) )
  }

   test("Trees have size") {
    val e = Tree.empty
    assert(e.size == 0)
    val t1 = single(1)
    assert(t1.size == 1)
  }

  test("Trees contains elements") {
    assert( ! empty.contains(0) )
    assert( single(0).contains(0) )
    assert( !single(0).contains(1) )
    val t123 = single(1).join(single(2).join(single(3)))
    assert( t123.contains(1) )
    assert( t123.contains(2) )
    assert( t123.contains(3) )
    assert( ! t123.contains(0) )
    assert( ! t123.contains(4) )
  }

  test("Tree elements can be removed") {
    val t123 = single(1).join(single(2).join(single(3)))
    assert( t123.remove(0) == t123 )
    assert( t123.remove(1) == single(2).join(single(3)) )
    assert( t123.remove(2) == single(1).join(single(3)) )
    assert( t123.remove(3) == single(1).join(single(2)) )
    assert( t123.remove(1).remove(2) == single(3) )
  }



}
