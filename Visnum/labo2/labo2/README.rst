Thomas Dagier
lundi 19 Avril 2021
TP sur la detection de couleurs dans le cadre du cours de Vision numérique.
Objectif : créer et utiliser une interface graphique afin de détecter l'angle d'inclinaison d'un volant et faisant de la detection de couleurs sur un flux vidéo.
Environnement : poetry (installé avec le lien dans l'énnoncé du labo)
Compilation/Exécution (dans le dossier thomas-dagier-joncour/labo2):

poetry shell

poetry run python3 labo2/wheel.py

(optionel) pour vérifier la sémantique: poetry run mypy labo2/wheel.py
(optionel) pour "sublimer ?!" le code : poetry black labo2/wheel.py