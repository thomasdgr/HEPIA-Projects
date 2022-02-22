# Visnum Labo 3

Projet réalisé par Thomas Dagier  dans le cadre du cours de vision numérique

## Description du projet

L'objectif de ce projet est de réaliser une application permettant d'utiliser un réseau de neurone pour créer un logiciel de reconnaissance de caractères (OCR). Seuls
les chiffres seront considérés. A partir du frontend, l'utilisateur peut dessiner un chiffre (de 0 à 9). Ensuite, il a la possibilité de recomencer le dessin, de l'envoyer pour le stocker dans la base de données (fichier json), dans ce cas, il faut selectionner le nombre correspondant au dessin dans la "drop-down list". Il peut aussi demander à l'OCR de s'entrainer (à partir des données présentes dans la base de données).

La majeur partie du projet reside dans le fait que l'utilisateur peut faire un dessin et demander à l'OCR de deviner le nombre. Dans ce cas, il retourne les probabilités qui correspondent au nombre trouvé (pas très précis).

## Fonctionnement du projet

Le projet est décomposé en 3 parties: 
    - le frontend (HTML, CSS, JS), pour l'interface utilisateur
    - le backend (python, API Keras de Tenserflow) pour la gestion de l'OCR
    - la liaison front-back (python, Fastapi), pour la gestion des routes

Il faut donc lancer le server frontend (qui tourne sous docker avec l'image nginx) avec la commande :

```
docker-compose up -d
```
Pour arrêter le container :
```
docker-compose down -v
```

Il faut aussi lancer le service uvicorn permettant de faire fonctionner fastapi (liaison frontend-backend) avec les commandes :

```
cd labo3/
poetry install
poetry shell
cd labo3/
uvicorn main:app --reload
```

Une fois les 2 services fonctionnels, il faut se rendre sur la page : [http://localhost:8080/frontend/]

Enjoy !


Pour tester le code (dans le dossier labo3/):

```
mypy labo3/main.py
mypy backend/back.py
```