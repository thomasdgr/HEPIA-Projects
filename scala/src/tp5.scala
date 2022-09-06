package ch.hepia.tp

//3 possibilités
enum TrafficLight1 {
  case Green, Yellow, Red
}

//8 possibilités
case class TrafficLight2(
  green: Boolean,
  yellow: Boolean,
  red: Boolean,
)

// on peut y accéder avec LightState.On par exemple
// /!\ si on fait du pattern matching dessus, on doit traiter tous les cas possibles
enum LightState {
  case On, Off, Blink
}

//18 possibilités
case class TrafficLight3(
  green: Boolean,
  yellow: LightState,
  red: LightState,
)

//Possibilités
// - Vert
// - Orange
// - Orange Clignote
// - Rouge
// - Rouge clignote
// - RougeOrange
// - Eteint

enum TrafficLight4 {
  case Green
  case Yellow( blink: Boolean )
  case Red( blink: Boolean )
  case RedYellow
  case Off
}


@main
def tp5 = {
    
}