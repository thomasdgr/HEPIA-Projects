package ch.hepia.tp

import java.time.LocalDate

case class Person(firstName: String, name: String, birthDate: LocalDate, address: Address)
case class Address(address: String, postCode: String, location: String, country: String)

case class Point2(x: Int, y: Int)
case class Segment(p1: Point2, p2: Point2)
def orientation(s: Segment): (Boolean, Boolean) = {
    def isDiag(i1: Int, i2: Int) = i1 == i2 || i1 == -i2
    s match {
        case Segment( Point2(_,y1), Point2(_,y2) ) if(y1 == y2) => (true,false)
        case Segment( Point2(x1,_), Point2(x2,_) ) if(x1 == x2) => (false,true)
        case Segment( Point2(x1,y1), Point2(x2,y2) ) if(isDiag(x1-x2, y1-y2)) => (true,true)
        case _ => (false, false)
    }
}

// Sans surcharge des oppérateurs 
/*case class Vec(x: Double, y: Double) {
    def plus(that: Vec) = Vec(x + that.x, y + that.y)
    def times(k: Double) = Vec(x * k, y * k)
    def minus(that: Vec) = this.plus(that.times(-1))
    def dot(that: Vec) = x * that.x + y * that.y
    def norme(that: Vec) = math.sqrt(this.dot(this))
}*/

// Avec surcharge des oppérateurs 
case class Vec(x: Double, y: Double) {
    def +(that: Vec) = Vec(x + that.x, y + that.y)
    def *(k: Double) = Vec(x * k, y * k)
    def -(that: Vec) = this + (that * -1)
    def *(that: Vec) = x * that.x + y * that.y
    def norme(that: Vec) = math.sqrt(this * this)
}

// on accroche cette méthode au type Vec 
// de cette manière on peut faire vec * x ou x * vec dans n'importe quel sens
// sinon on aurait pu faire seulement vec * x
extension(x: Double) {
    def *(v: Vec) = v * x
}

@main
def tp4 = {
    val myAddr = Address("oui", "01280", "Prevessin", "France")
    println(s"Fonction personne: ${Person("thomas", "dagier", LocalDate.now(), myAddr)}")
    println(s"Fonction orientation: ${orientation(Segment(Point2(1,1), Point2(2,2)))}")
}