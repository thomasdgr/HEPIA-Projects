package ch.hepia.scala.eval2

import org.scalatest.funsuite.AnyFunSuite

class Tree1Suite extends AnyFunSuite {

  import Tree.*

   test("Trees have size") {
    val e = Tree.empty
    assert(e.size == 0)
    val t1 = single(1)
    assert(t1.size == 1)
  }

  test("Trees have depth") {
    val e = Tree.empty
    assert(e.depth == 0)
    val t1 = single(1)
    assert(t1.depth == 1)
  }

  test("Trees can be joined") {
    val t12 = single(1).join(single(2))
    val t34 = single(3).join(single(4))
    val t1234 = t12.join(t34)
    assert(t12.size == 2 )
    assert(t34.size == 2 )
    assert(t1234.size == 4)
    assert(t12.depth == 2 )
    assert(t34.depth == 2 )
    assert(t1234.depth == 3)
  }

  test("Join ignores empty") {
    val t1 = single(1)
    val t1l = single(1).join(empty)
    val t1r = empty.join(single(1))
    assert(t1l.size == 1 && t1l.depth == 1 )
    assert(t1r.size == 1 && t1r.depth == 1 )
    assert(t1 == t1l)
    assert(t1 == t1r)
  }

  test("Trees can be rotated") {
    val t1 = single(1)
    val t12 = single(1).join(single(2))
    val t123 = t12.join(single(3))
    val t123bis = single(1).join( single(2).join(single(3)))
    assert(t123 != t123bis )
    assert( t1.rotateRight == t1 )
    assert( t12.rotateRight == t12 )
    assert( t123.rotateRight == t123bis )
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
    assert( t123.remove(1).size == t123.size - 1 )
    assert( t123.remove(1) == single(2).join(single(3)) )
    assert( t123.remove(2) == single(1).join(single(3)) )
    assert( t123.remove(3) == single(1).join(single(2)) )
    assert( t123.remove(1).remove(2) == single(3) )
  }
}