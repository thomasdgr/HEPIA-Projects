# Les tuples

Les **buts** de ce TP sont:
  - Découvrir les tuples
  - Expérimenter le pattern matching

## Swap

Implémentez la fonction `swap`. Celle-ci inverse les arguments du tuple.

```scala
def swap( nums: (Int,Int) ): Int = ???

swap( (i,j) ) == (j,i) //Pour tout i, j
swap( swap( x ) ) == x //Pour tout x
```
## Points dans l'espace

Utilisez des tuples pour représenter un point dans un espace 2D. 
Implémentez une fonction distance entre deux points.

## Coordonnées Longitude/Latitude

On peut utiliser deux systèmes différents pour représenter des coordonnées géographique. Le système DMS (degré, minute, seconde), et
le système en degré décimal. Pour plus d'info: [Coordonnées_géographiques#Position](https://fr.wikipedia.org/wiki/Coordonn%C3%A9es_g%C3%A9ographiques#Position).

De même, on peut soit indiquer les longitudes en Est/Ouest et les latitudes en Nord/Sud, ou bien utiliser un signe pour distinguer les hémisphères.

On aimerait convertir les coordonnées de la notation DMS avec direction cardinale, en notation degrés décimaux signés.

Par exemple: 

```
Genève en DMS:
  Latitude: 46° 12' 15.8394" N
  Longitude: 6°  8' 35.52"   E

Genève en degré décimaux signés
  Latitude: 46.2044°
  Longitude: 6.143246°
```

Utiliser des tuples pour représenter les coordonnées. 
