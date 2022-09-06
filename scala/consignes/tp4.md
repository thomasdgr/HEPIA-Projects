# Les cases class 

Les **buts** de ce TP sont:
  - Découvrir les `cases class`
  - Représenter des connaissances
  
## Représentation de données

Une personne est représentée par:

- son prénom
- son mom
- sa date de naissance
- son adresse postale:
  - rue et numéro
  - code postal
  - localité
  - pays
  
  Proposer une représentation à l'aide de `case class`.
  
## Pattern matching
  
Soit un la définition suivante:

```scala
case class Point(x:Int,y:Int)
case class Segment(p1:Point,p2:Point)
```
  
Implémenter une méthode la méthode suivante:

```scala
def orientation( s: Segment ): (Boolean,Boolean)
```

Cette méthode retourne:
- `(true,false)` si le segment est horizontal
- `(false,true)` si le segment est vertical
- `(true,true)` si le segment est diagonal (+ ou - 45°)
- `(false,false)` dans tous les autres cas

## Vecteurs 

Représenter des vecteurs en 2D par des `case class`.

Ajouter des méthodes permettant de gérer les opérations suivantes:

- Addition et soustraction vectorielle
- Produit entre un scalaire et un vecteur
- Produit entre deux vecteurs (produit scalaire)
- Norme
