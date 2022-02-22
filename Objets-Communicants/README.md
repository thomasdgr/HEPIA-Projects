# Projet OC 2021: Equipe Kentus Rodvald ltd.

## Description

Réalisé par Xavier Perret, Quentin Rod et Thomas Dagier entre le 01 Novembre 2021 et le 13 Décembre 2021, ce projet intervient dans le cadre du cours d'Objets Communicants du 5eme Semestre ISC à HEPIA. 

Le but de ce projet est d'avancer au maximum dans la réalisation d'un outil permettant de localiser des personnes sur un evenement et de réaliser des statistiques à partir de tag RFID que chaque participant porterait.

Le projet est séparé en plusieurs parties distinctes:

- le frontend: réalisé avec `Fluter` pour interface web et mobile.
- le backend: réalisé en python avec `Fast API - Uvicorn`.
- la base de données: réalisée avec `MySQL` et supportée par `Docker`. 

## Execution du projet:

Attention: l'ordre de lancement des composants a une importance a une importance

### Pour lancer la base de données:
- `cd ./bdd/`
- `sudo docker-compose up -d`
- Pour lancer la console de la db:
    - `docker-compose exec db mysql -u user -p` (le mot des passe est "test")
- Pour arrêter la db:
    - `sudo docker-compose down -v`

### Pour lancer le backend:

- Nécéssite FastAPI: `pip install fastapi`
- Nécéssite Uvicorn: `pip install "uvicorn[standard]"`
- Nécéssite MySQL pour python: `pip install mysql.connector`
  
Une fois tout installé:
- `cd ./backend/`
- `uvicorn api:app --reload --host 0.0.0.0`

### Pour lancer le gestionnaire de lecteur:
- `cd ./raspberry_files/`
- `python3 main.py config.yaml`

### Pour lancer le frontend:
- Nécéssite Flutter : [doc d'installation](https://docs.flutter.dev/get-started/install)
- `cd flute/`
- `flutter run`
