# Travail Pratique

Hessncf est une application web réalisée dans le cadre de notre 4eme semestre à HEPIA. Créé par Dorian Bernasconi et Thomas Dagier, ce projet a pour but de mettre en application nos connaissances et les contenus des cours de Mr Jérémy Gobet et Mr Stéphane Malandain.

Le GIT du cours:
`ssh://git@ssh.hesge.ch:10572/jeremy.gobet/app-et-archi-web.git`

Le GIT depuis lequel le projet est forké:
`git clone ssh://git@ssh.hesge.ch:10572/jeremy.gobet/app-et-archi-web-tp-2020.git`

## Description du projet

Le travail réalisé au cours de ce semestre a pour but de récupérer les données de la SNCF (qui implémente l'API publique Navitia) afin d'en faire un usage détourné et parodié. L'objectif est de proposer des fonctionnalités drôles comme le temps de retard des trains cummulé sur un jour, le nombre de train qui sont en retard, un classement des pires trajets, des actualités ou des succès à débloquer qui seraient propres aux utilisateurs qui se connectent sur le site...

Dans un registre plus sérieux, l'application permet aussi de trouver un trajet entre deux points pour une heure et une date pécise.

Ce projet est réalisé en 2 temps :
- l'application web (HTML5, CSS et JavaScript)
- l'architecture web (api rest crud en JavaScript interagissant avec une base de données -> fichiers json)

### Réccupérer le projet

Le projet est disponible sur l'hébergement Git (gitedu.hesge.ch).
Cloner le projet localement avec la commande git suivante:

`git clone ssh://git@ssh.hesge.ch:10572/dorian.bernasco/app-et-archi-web-tp-2020.git`

### Structure

Le projet contient deux dossiers:

- **frontend**: Contient le site public
- **backend**: Contient le serveur Node

### Démarrer le serveur

La partie publique est servie par le serveur sur Node. Vous devez avoir Node installé sur votre machine pour démarrer cette application Web.

Accédez au dossier contenant le serveur Node :

`cd backend/`

Installez les dépendances :

`npm install`

Démarrez le serveur Node :

`node server.js`

Vous pouvez ensuite visualiser le site en local sur un navigateur: **localhost:8080**

**Important: Il est recommandé d'utiliser le navigateur firefox lors de l'utilisation du site**

Premièrement car l'affichage n'est pas tout à fait le même en fonction des navigateur.

Deuxièmement, il faut que la langue du navigateur soit en francais: dans le cas contraire, la balise récupéprant l'heure dans la page "prévoir mon trajet" ne fonctionne pas correctement (la base de temps anglaise étant différente).

**pout téléphone il y a moins de problèmes avec les navigateurs mais firefox est également conseillé**


### Stopper le server

Pour stopper le serveur Node, utilisez la commande **CTRL + C**

### Architecture du projet

              +------------+
              |            |
              |            |
           +--+  Frontend  +--+
           |  |            |  |
           |  |            |  |
           |  +------------+  |
           |                  |
           |                  |
           |                  |
           |                  |
           v                  v
    +-------------+    +-------------+
    |     API     |    |     API     |
    +-------------+    +-------------+
    |   Database  |    |             |
    |   Backend   |    |    SNCF     |
    |   NODE.JS   |    | API public  |
    |             |    | Ressources  |
    +-------------+    +-------------+

- Frontend: Projet HTML5, CSS3, JS
- Backend: Exposition d'une API REST sur NODE.JS pour la gestion des classements et des succès (les succès sont propres à l'utilisateur qui se connecte)
- SNCF: (utilise navitia : http://doc.navitia.io/)
    Accès    : https://api.sncf.com/v1
    Username : 3875f1e7-0db3-40f4-9cfc-220cbad4b6e3
    Password : 

### Fonctionnalités

Story Board :

| Exigences   |             Temps               |          Pages            |        Notation            |          Trajet            |
|:------------|:--------------------------------|:--------------------------|:---------------------------|:---------------------------|
| MUST HAVE   | Affichage des minutes de retard | Page d'accueil | Classement des jours / endroits où les retards sont les plus importants (Implémentation backend) | |
|  |  | Page des classements |  |  | 
|  |  | Page "À Propos" (informations sur les auteurs, le projet...) |  |  |
|:------------|:--------------------------------|:--------------------------|:---------------------------|:---------------------------|
| SHOULD HAVE |  Affichage des minutes sur d'autres période de temps (séléctionner un jour/mois...) | Page "Succès" | Atteindre des succès sur une periode de temps dépassant 1 jour (Implémentation backend) |  |    
|  |  |  |  | calculer un intiéraire |
|:------------|:--------------------------------|:--------------------------|:---------------------------|:---------------------------|
|NICE to HAVE |  En fonction de la station de départ et d'arrivée, calcul la probabilité que le train soit en retard |  |  |  |
|  |  |  Page "En bref": des infos sur la SNCF : grèves, la probabilité que le train soit en retard, accidents... |  |  |

### Organisation

Pas de travail réparti, nous faisons tout ensemble de A à Z.
Le temps de travail varie globalement en fonction des autres cours (2 à 3 heures par semaines au début puis 8 à 10 heures par semaines les 2-3 dernières).

### Interface API REST CRUD

Le backend permet essentiellement de stocker des données. Les classements sont stockés dans différents fichiers en fonction de leur type. Il est possible de mettre à jour certaines données, d'en ajouter, d'en supprimer et surtout de les récuperer pour pouvoir les afficher sur le site

D'autre part, il est possible de stocker des succès. Ces derniers sont propres à l'utilisateur qui se sera connecté sur le site. Il a la possibilité d'en ajouter et 
de voir la liste de tous ses succès.

Pour l'authentification, lorsque l'utilisateur envoie ses identifiants le serveur va alors vérifier qu'ils correspondent bien à ceux enregistrer en dur sur le serveur. Une fois que les identifiants de l'utilisateur sont vérifiés le serveur va alors envoyé au frontend un token qui sera alors stocké dans une variable dans le javascript. Le token lui expire en 5 minutes pendant lesquelles l'utilisateur peut alors ajouter des succès sur son profil. Il est ensuite possible de se déconnecter ce qui va alors modifier le token enregistré dans le serveur.

Pour la création du token et pour ça vérification on utilise un "secret" qui est une clé de 64 bytes enregistrer dans le fichier .env et généré grâce à la commande => require('crypto').randomBytes(64).toString('hex')

### Contact

### Auteurs

- Identifiant: @thomas.dagierjo
- Mail: thomas.dagier-joncour@etu.hesge.ch

- Identifiant: @dorian.bernasco
- Mail: dorian.bernasconi@etu.hesge.ch

#### Assistant

- Identifiant: @michael.minelli
- Mail: michael-jean.minelli@hesge.ch

#### Applications Web

- Identifiant: @jeremy.gobet
- Mail: jeremy.gobet@hesge.ch

#### Architectures Web

- Identifiant: @stephane.malandai
- Mail: stephane.malandain@hesge.ch