package ch.hepia.tp

import org.scalatest.funsuite.AnyFunSuite

class IntStackSuite extends AnyFunSuite {

  import IntStack.*

  val stack123 = Empty.push(1).push(2).push(3)


  test("Empty stack has zero size") {
    assert( Empty.isEmpty )
    assert( Empty.size == 0 )
  }

  test("Can push elements") {
    assert( ! stack123.isEmpty )
    assert( stack123.size == 3 )
  }

  test("Can pop elements") {
    val s0 = stack123
    val (t,s1) = s0.pop
    assert( t == 3 )
    assert( s1.size == 2 ) 
  }

  test("Can get bottom element") {
    assert( stack123.bottom == 1 )
  }

  test("Can rotate elements" ) {
    val r = stack123.rotate
    assert( r.bottom == 3 )
    assert( r.size == 3 )
    val (t,r1) = r.pop
    assert(t==2)
  }

  test("Can reverse stack" ) {
    val r0 = stack123.reverse
    val (t1,r1) = r0.pop
    val (t2,r2) = r1.pop
    val (t3,r3) = r2.pop
    assert(t1 == 1)
    assert(t2 == 2)
    assert(t3 == 3)
    assert(r3.isEmpty)
  }

  test("Can pushAll") {
    val stack456 = Empty.push(4).push(5).push(6)
    val s = stack123.pushAll(stack456)
    assert(s.size == 6)
    val (t,s1) = s.pop
    assert(t==6)
    assert(s1.size==5)
    assert(s.bottom==1)
  }
}