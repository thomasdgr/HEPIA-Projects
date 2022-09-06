# TP 1

Les buts de ce TP sont:
- de configurer un environement de travail; 
- prendre en main l'outil SBT;
- découvrir la syntaxe de base de Scala 3. 

## Installation de SBT

Installez l'outil SBT (obligatoire) pour compiler et exécuter le code. Celui-ci dépend de Java.

Plusieurs options d'installation:

- Votre distribution (Linux)
- Le script [sbt-extras](https://github.com/dwijnand/sbt-extras) (Linux ou MacOS)
- Le [site officiel](https://www.scala-sbt.org/) (Windos ou MacOS)
- Cloner le site du cours, allez à la racine du dépôt GIT, et lancez `sbt`, les commandes suivantes se lanceront
  dans le shell `sbt` directement.

## Tester SBT

- Pour compiler le projet: `compile`. La première fois il télécharge tout ce dont il a besoin.
- Pour accéder à un interpréteur Scala: `console`.
- Exécutez le _Hello, World_ avec: `runMain  ch.hepia.tp.hello`.

## Premier TP

- Etudiez le fichier `src/helloWorld.scala`
- Etudier le fichier `src/tp1.scala`
- Exécutez ce dernier fichier avec `runMain ch.hepia.tp.tp1`
- Implémenter les fonctions, jusqu'à ce que tout soit bon

### ATTENTION

Les seuls mots-clés autorisés sont `val`, `def`, `if` et `else`. Tous les autres
sont strictement interdits (pas de `var`, `while`, `return`, etc.)
