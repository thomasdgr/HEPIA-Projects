package ch.hepia.scala.tp7


/* Implémentez les fonctions suivantes. 
 */


/* Il faut commencer par bien identifier les types
   albums: List[Album]
   tracks: Map[(String, Track)]
*/

case class Album( title: String, artist: String, year: Int )
case class Duration( minutes: Int, seconds: Int )
case class Track( title: String, duration: Duration )

val albums = List(
  Album( "Mit Gas", "Tomahawk", 2003 ),
  Album( "Pork Soda", "Primus", 1993 ),
  Album( "Brown Album", "Primus", 1997 ),
  Album( "Distraction Pieces", "Scroobius Pip", 2011 )
)

val tracks = Map(
  "Mit Gas" -> List(
    Track( "Mayday", Duration( 3, 32 ) )
  ),
  "Pork Soda" -> List(
    Track( "DMV", Duration( 4, 58 ) ),
    Track( "Mr. Krinkle", Duration( 5, 27 ) )
  ),
  "Brown Album" -> List(
    Track( "Fisticuffs", Duration( 4, 25 ) ),
    Track( "Camelback Cinema", Duration( 4, 0 ) ),
    Track( "Kalamazoo", Duration( 3, 31 ) )
  ),
  "Distraction Pieces" -> List(
    Track( "Let 'Em Come", Duration( 4, 25 ) ),
    Track( "Domestic Silence", Duration( 3, 58 ) )
  )
)

/* Retourne la liste de morceaux associés à un artiste */
def tracksOf( artist: String ): List[Track] =
  //albums.filter( alb => alb.artist == artist ).flatMap{ alb_filtered => tracks( alb_filtered.title ) }
  albums.filter( alb => alb.artist == artist ).map( alb_filtered =>  alb_filtered.title ).flatMap( tracks )
  /*for {
      alb <- albums
      if alb.artist == artist
        alb_filtered <- alb.map( _.title )
        alb_filtered.flatMap( tracks )

  }yield ... */
  albums.filter( album => album.artist == artist ).flatMap( album => tracks(album.title) )

/* Retourne la liste de tous les morceaux de moins de 4 minutes */
def shortTracks: List[Track] = 
  tracks.flatMap{ m => m._2.filter( t => t.duration.minutes < 4 ) }.toList
  //tracks.flatMap( ( _, v )  => v ).toList.filter( t => t.duration.minutes < 4 )
  /*for {
      ( _, v ) <- tracks.toList
      t <- v
      if t.duration.minutes < 4
  } yield t*/
  //tracks.values.flatten.filter( track => track.duration.minutes < 4 ).toList

/* Retourne les titres des morceaux antérieurs à une année */

def titlesBefore( year: Int ): List[String] = 
  albums.filter( a => a.year < year ).flatMap{ a => tracks(a.title) }.map( i => i.title ).toList
  //albums.filter( _.year < year ).map( _.title ).flatMap( tracks ).map( _.title )
  //albums.filter( _.year < year ).flatMap( a => tracks(a.title) ).map( _.title )
  //albums.filter( album => album.year < year ).flatMap( album => tracks(album.title) ).map( track => track.title )

/* Calcule la durée totale de tous les morceaux disponibles.
   REMARQUE: ont veut que les secondes soient inférieures à 60 mais les
   minutes peuvent dépasser ce total.
 */
def totalDuration: Duration = {
    def dur2sec( dur: Duration ) = dur.minutes*60 + dur.seconds
    def sec2dur( sec: Int ) = Duration( sec/60, sec%60 )
    def sum( d1: Duration, d2: Duration ) = sec2dur( dur2sec(d1) + dur2sec(d2) )
    sum( albums.flatMap( a => tracks(a.title) ).map( t => t.duration ).reduce( sum ), Duration( 0, 0 ) )
    
    //def durationFromSeconds(seconds: Int) : Duration = Duration(seconds/60, seconds%60)
    /* val total = tracks.values.flatten.map( t => t.duration.minutes * 60 + t.duration.seconds ).sum
    durationFromSeconds(total) */
}