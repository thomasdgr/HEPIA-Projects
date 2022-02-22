# Maven

Maven est un gestionnaire de projets et d'automatisation de production pour l'écosystème Java.

Le fichier `pom.xml` décrit le projet avec ses dépendances.

### Modification du fichier pom.xml

Adaptez le fichier `pom.xml` selon votre projet :

- Verifiez la version de java
- Changez le nom du projet/package dans `groupId` et `artifactId`
- Modifiez la configuration du plugin `exec-maven-plugin` pour pointer sur votre classe principale contenant votre `main`

### Exécutez votre projet

- compilation et téléchargement des dépendances. Produit un `jar` dans le dossier `target`.

```
mvn package
```

- exécutez à l'aide de java et du classpath:

```
java -cp target/my-app-0.1.jar ch.hepia.my_app.App
```

- ou, à l'aide du plugin `exec-maven-plugin`:

```
mvn exec:java
```

### Exécutez les tests uniquement

```
mvn test
```

### Notes

Le plugin `maven-assembly-plugin` est configuré et permet d'embarquer les dépendances dans un seul `jar`.


### Nouvelles dépendances

Pour ajouter une nouvelle dépendance, vous pouvez l'ajouter dans la section `<dependencies>`. Le site [mvnrepository](https://mvnrepository.com) est une référence pour la mise à disposition de librairies de l'écosystème de la JVM (Java, Scala, Kotlin...)

Vous pouvez par exemple ajouter la librairie JavaFX pour réaliser des interfaces graphiques en ajoutant le code ci-dessous dans votre fichier `pom.xml`:

```
<!-- https://mvnrepository.com/artifact/org.openjfx/javafx -->
<dependency>
    <groupId>org.openjfx</groupId>
    <artifactId>javafx-controls</artifactId>
    <version>14</version>
    <type>pom</type>
</dependency> 
```