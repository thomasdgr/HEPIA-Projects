# TP 2

Les buts de ce TP sont:
- Montrer le passage d'arguments de ligne de commande à la fonction main
- Découvrir une caractéristique des fonctions récursives

## Tests

Lisez attentivemet le code de `tp2.scala`, essayez de prédire le fonctionement des fonctions.

Gardez la fonction `dumbCount1` commentée et exécutez la fonction `dumbCount2` avec les paramètres
suivants:
  - 1'000
  - 10'000
  - 100'000
  - 1'000'000
  
  
Pour cela vous pouvez tapper dans sbt:

```
 runMain ch.hepia.tp.tp2 10000
```

Les résultats correspondent-ils à vos attentes ?

Maintenant commentez `dumbCount2` et décommentez `dumbCount2`. Répétez l'expérience avec les mêmes
valeurs d'arguments.

Que constatez vous ? Pourquoi ?

## Evaluation par substitution

Pour expliquer ce qui se passe, développez les appels suivants en utilisant l'approche vue en cours:

``` scala
dumbCount1( 3 )

dumby( 3, 0 )
```

Dans la mesure où l'ordre ne change pas le résultat, on va choisir de coller à
ce que ferait la JVM lors de l'exécution. Pour cela développez toujours les `if`
en premier, et développez les arguments avant les appels de fonction.

Que constatez vous ? Quel est l'impact sur la pile d'exécution ?
