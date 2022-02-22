# poo2020exercices

Ceci est la structure de bases pour l'ensemble de vos rendus individuels

Gardez toujours la structure décrite ci-dessous:

```
.
|- serie1
   |- ex1.2/MonApp.java
   |- ex1.2/Exercice.java
|- serie2
   |- ex1.3/Main.java
|- serie2
   |- ex1.1
      |- pom.xml
      |- src/...
      |- ...
```

- Un fichier *.java commence toujours par une majuscule est respecte la convention `CamelCase`.
- Pour être exécutable, il est nécessaire d'y avoir une méthode `main`
- Le nom du fichier est libre s'il n'est pas imposé dans la consigne

commandes maven :
   mvn package
   mvn exec:java -Dexec.args="arguments"