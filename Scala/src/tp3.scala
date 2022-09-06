package ch.hepia.tp

def swap( ij: (Int, Int) ): (Int,Int) = {
  val (i,j) = ij
  (j, i)
}

def swap2( ij: (Int, Int) ): (Int,Int) =
  (ij._2, ij._1)

type Point = (Double,Double)

def dist( p: Point, q: Point ): Double = {
  val (px,py) = p
  val (qx,qy) = q
  def sq(x:Double) = x*x
  math.sqrt( sq(px-qx) + sq(py-qy) )
}

type DMS = (Int,Int,Double,String)
type DD = Double
type CoordDMS = (DMS,DMS)
type CoordDD = (DD,DD)

def convert( coord: CoordDMS ): CoordDD = {
  def dms2dd(h:Int,m:Int,s:Double) =
    h + m/60.0 + s/3600
  def convertLat(lat:DMS):DD = lat match {
    case (h,m,s,"N") => dms2dd(h,m,s)
    case (h,m,s,"S") => -1 * dms2dd(h,m,s)
  }
  def convertLong(long:DMS):DD = long match {
    case (h,m,s,"W") => -1 * dms2dd(h,m,s)
    case (h,m,s,"E") => dms2dd(h,m,s)
  }
  val (lat,long) = coord
  (convertLat(lat),convertLong(long))
}

@main
def tp3 = {
    println( s"Fonction swap: ${swap( (1,2) ) == (2,1)}" )
    println( s"Fonction dist: ${dist( (1,2) , (3,4) )}" )
    println( s"Fonction convert: ${convert( ( (1,1,1.0,"S"), (1,1,2.0,"W") ) )}" )
}
