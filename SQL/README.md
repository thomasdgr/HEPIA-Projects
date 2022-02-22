# SBD Mc Donald

Projet réalisé par Quentin Rod, Thomas Dagier et Dorian Bernasconi dans le cadre du cours de base de données du 4eme semestre.

## Description du projet

Le travail consiste à réaliser une base de données materialisant la partie "commandes au guichet" du fonctionnement du Mc Donald's. Afin de réaliser le travail, nous devons construire un diagramme Entité-Association puis réaliser le diagramme relationnel. Nous pourrons ensuite obtenir le schéma relationnel correspondant. Une fois ces tâches réalisées, nous devons modéliser la base de données conteneurisée avec docker. Pour cela, nous utilisons une partie réduite du projet et créons le script SQL servant à charger notre base de données.

Notre base de données contient des entrées pour chacune des tables relatives aux articles disponibles au mcdo. Elle est aussi composée des fonctionnalités suivantes:

- Un trigger pour vérifier que le prix d'un article soit valide avant insertion. Cela permet d'imposer à tout le monde une limite de prix.
- Une vue permet de donner le prix de l'ensemble des menus en fonction de ses articles. Cela est très utile si l'on veut une vue d'ensemble des menus proposés.
- Une seconde vue permet de montrer les commandes composées d'au moins un article ET un menu. Cela permet d'identifier ce que les clients prennent généralement en plus d'un menu.
- Une procédure stockée qui retourne le prix d'un article en fonction de son nom.
- Une procédure stockée qui retourne le prix total d'un menu.

Une grande force de notre modèle réside dans le fait que nous pouvons facilement différencier les commandes faites par les clients. Ces derniers ont le choix entre différents articles (individuels) ainsi que des menus (obligatoirement composé d'un plat, d'une boisson et d'un accompagnement). 

Cependant, même s'il nous est possible de conserver un historique des commandes, on ne peut pas voir les articles qui les composent si ces derniers ne sont plus disponibles à la vente. 

Un point faible du modèle EA se répercutant sur le modèle relationnel est qu'un même article peut-être à la fois un accompagmement, une boission et un plat principal.

Le passage du modèle EA vers relationnel a entraîné un ajustement de certains liens. Il s'agit de la cardinalité (1,n) transformée en (0,n).

## Lancer la base de données

```
docker-compose up -d
```

Si jamais il y a des erreurs de permissions pour pouvoir lancer la base de données, verifier que les droits sont attribués pour le fichier docker-compose.yml, le dossier mcdo/ ainsi qu le dossier dump/

Une fois lancée, se connecter à phpmyadmin: [http://localhost:8000]

Ou alors utiliser le client mysql:

- `docker-compose exec db mysql -u user -p`

Puis entrer le mot de passe : "test"

## Fermer la base de données et supprimer le volume en local 
```
docker-compose down -v
```