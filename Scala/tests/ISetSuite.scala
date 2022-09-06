package ch.hepia.tp

import org.scalatest.funsuite.AnyFunSuite

class ISetSuite extends AnyFunSuite {
  test("Create a set with a single element") {
    val s0 = ISet.single("foo")
    assert(s0.contains("foo"))
    assert(! s0.contains("goo") )
  }
  test("Add elements to ISet") {
    val s0 = ISet.empty[Int]
    assert( ! s0.contains(12) )
    val s1 = s0.add(12)
    assert( s1.contains(12) )
    assert( ! s1.contains(21) )
    val s2 = s1.add(21)
    assert(s2.contains(21))
  }
  test("Union of ISets") {
    val m2 = ISet[Int]( _ % 2 == 0 )
    val m3 = ISet[Int]( _ % 3 == 0 )
    val s = m2.union(m3)
    assert( s.contains(2) )
    assert( s.contains(9) )
    assert( ! s.contains(5) )
  }
  test("Intersection of ISets") {
    val m2 = ISet[Int]( _ % 2 == 0 )
    val m3 = ISet[Int]( _ % 3 == 0 )
    val s = m2.intersection(m3)
    assert( ! s.contains(2) )
    assert( ! s.contains(9) )
    assert( s.contains(6) )
  }
  test("Difference of ISets") {
    val m2 = ISet[Int]( _ % 2 == 0 )
    val m3 = ISet[Int]( _ % 3 == 0 )
    val s = m2.difference(m3)
    assert(  s.contains(2) )
    assert( ! s.contains(9) )
    assert( ! s.contains(6) )
  }
}