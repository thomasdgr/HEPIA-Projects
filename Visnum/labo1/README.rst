Thomas Dagier
lundi 15 Mars 2021

TP sur Hough dans le cadre du cours de Vision numérique.
Objectif : implémenter l'alogrithme de Hough pour détécter les droites dans une image.
Environnement : poetry (installé avec le lien dans l'énnoncé du labo)

Compilation/Exécution (dans le dossier thomas-dagier-joncour/labo1):
	
	1) poetry shell 
	
	2) poetry run python3 labo1/hough.py labo1/chess.png 0.1 0.5
		- labo1/hough.py : le nom du programme
		- labo1/chess.png : le chemin vers l'image à analyser
		- 0.1 : le seuil (recommandé) compris entre 0 et 1  à appliquer lors de la binarisation
		- 0.5 : le seuil (recommandé) compris entre 0 et 1, à appliquer lors du choix des meilleures droites
	
	3) (optionel) pour vérifier la sémantique: poetry run mypy labo1/hough.py
	
	4) (optionel) pour "sublimer ?!" le code : poetry black labo1/hough.py
