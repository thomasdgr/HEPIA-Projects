# Projet d'orientation
## Description du projet

Travail de semestre réalisé par Thomas Dagier, Antoine Blancy et Gustavo Pertuzati dans le cadre du module "projet d'orientation". Ce projet a pour but de réaliser un jeu similaire à [Plage Inc.](https://fr.wikipedia.org/wiki/Plague_Inc.) basé sur le COVID-19. 

## Le jeu 
Vous commencez votre aventure au moment où le monde entend parler du covid. Votre objectif est simple: erradiquer l'espèce humaine. Pour cela, vous devrez faire progresser votre virus à travers le temps en le faisant évoluer grâce à des points de compétences gagnés au cours de la partie.

Mais la tâche ne sera pas simple puisque les pays du monde entier se défendent contre votre virus. Il vous faudra donc faire des choix dificiles afin de privilègier certains asepcts de votre virus comme le taux de mortalité ou celui de propagation.

Tout le long de la partie, vous pourrez comparer votre progression avec celle du vrai covid-19 et ainsi determiner qui de vous ou du covid-19 est le meilleur.

## Prérequis 
Ce projet utilise
```
- Java 15
- Maven
- Docker-compose
```

## Récupérer le projet
Le projet est disponnible sur gitedu.hesge.ch, pour le récupérer localement il faut cloner le projet avec la commande suivante:
```
git clone https://gitedu.hesge.ch/thomas.dagierjo/covid-manager.git
```

## La base de données

Pour lancer la base de donnée, il faut se rendre dans le dossier *bdd/*, puis lancer le server avec la commande:

```
docker-compose up
```
Ou bien, si on ne veut pas "occuper" un terminal:
```
docker-compose up -d
```


## Compiler le projet
Pour compiler le projet, il faut se rendre dans le dossier *covid_project/*, et ensuite faire la commande:
```
mvn package
```

## Lancer le projet
Pour executer le programme, il faut utiliser la commande:

**Attention! Pour pouvoir utiliser le programme, il faut que la base de donnée soit en train de tourner!!**

```
mvn exec:java
```

## Contact

### Auteurs
* Thomas Dagier (thomas.dagier-joncour@etu.hesge.ch)
* Gustavo Pertuzati (gustavo.pertuzati@etu.hesge.ch)
* Anotoine Blancy (antoine.blancy@etu.hesge.ch)
