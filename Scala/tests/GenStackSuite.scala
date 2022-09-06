package ch.hepia.tp6

import org.scalatest.funsuite.AnyFunSuite

class GenStackSuite extends AnyFunSuite {

  import Stack.*

  test("Map") {
    val s123 = Empty.push(3).push(2).push(1)
    assert( s123.map(identity) == s123 )
    assert( s123.map( _ * 2 ) == Empty.push(6).push(4).push(2) )
  }

  test("Filter") {
    val s123 = Empty.push(3).push(2).push(1)
    assert( s123.filter( _ < 10 ) == s123 )
    assert( s123.filter( _ % 2 == 0 ) == Empty.push(2) )
    assert( s123.filter( _ % 2 == 1 ) == Empty.push(3).push(1) )
  }


  test("Reduce") {
    val s123 = Empty.push(3).push(2).push(1)
    assert( s123.reduce(1)(_*_) == 6 )
    assert( s123.reduce(0)(_+_) == 6 )
    assert( s123.reduce(0)( _ max _ ) == 3 )
  }

  test("Zip") {
    val s123 = Empty.push(3).push(2).push(1)
    val sABC = Empty.push("A").push("B").push("C")
    assert( s123.zip(s123) == Empty.push((3,3)).push((2,2)).push((1,1)))
    assert( s123.zip( Empty.push(true) ) == Empty.push((1,true)) )
    assert( Empty.push(true).zip(s123) == Empty.push((true,1)) )
    assert( sABC.zip(s123) == Empty.push(("A",3)).push(("B",2)).push(("C",1)) )
  }
}