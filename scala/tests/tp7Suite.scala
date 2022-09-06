package ch.hepia.scala.tp7

import org.scalatest.funsuite.AnyFunSuite


class TP7Suite extends AnyFunSuite {

  test( "tracksOf" ) {
    assert( tracksOf("Justin Bieber").isEmpty )
    assert( tracksOf("Tomahawk") == List( Track( "Mayday", Duration( 3, 32 ) ) ) )
    assert( tracksOf("Primus").size == 5 )
  }

  test( "shortTracks" ) {
    assert(
      shortTracks.toSet == Set(
        Track( "Mayday", Duration( 3, 32 ) ),
        Track( "Kalamazoo", Duration( 3, 31 ) ),
        Track( "Domestic Silence", Duration( 3, 58 ) )
      )
    )
  }

  test( "titlesBefore" ) {
    assert( titlesBefore( 1928 ).size == 0 )
    assert( titlesBefore( 2020 ).size == 8 )
    assert(
      titlesBefore( 2000 ).toSet == Set(
        "DMV",
        "Mr. Krinkle",
        "Fisticuffs",
        "Camelback Cinema",
        "Kalamazoo"
      )
    )
  }

  test( "totalDuration" ) {
    assert( totalDuration == Duration( 34, 16 ) )
  }
}
