# Approche théorique

## La modélisation des déplacements

Au regard de l'importance que jouent les (+TPG_a) dans les déplacements quotidiens des habitants de la ville de Genève, il apparaît essentiel de modéliser ce réseau pour réaliser une simulation précise qui permetterait de contribuer à la planification urbaine du canton de Genève.

Dans la vie de tous les jours, un trajet est associé à une personne, une raison de se déplacer, un moyen de transport cohérent, un point de départ et un point d'arrivée. Pour notre modélisation, il est possible de se déplacer à pied, à vélo, en voiture ou en transports en commun.

Ensuite, une personne peut se déplacer pour différentes raisons comme le travail, l'école, les loisirs, les courses... Une personne se rend aussi d'un point A (par exemple, une habitation) à un point B (par exemple, un lieu de travail) en choisissant un moyen de transport adapté au trajet effectué (on ne voudrait pas qu'une personne prenne sa voiture pour un trajet de 200 mètres ou qu'une autre se déplace à pied sur 35 kilomètres). Cette personne doit également suivre un calendrier cohérent comme le fait d'aller au travail à 8 h 00 ou de faire ses courses à un horaire raisonnable. Toute la modélisation de cette répartition statistique est réalisée en parallèle par Ilias N'hairi [@nhairi_project]. Cependant, il est alors nécessaire d'intègrer le réseau des (+TPG_a) afin d'avoir une simulation plus cohérente de la mobilité genevoise.

En outre, ceci montre déjà l'étendue du travail à faire simplement pour que des gens se déplacent. Mais il faudrait aussi avoir une carte précise sur laquelle les gens peuvent suivre un itinéraire. Et ce, sans penser à la logique du simulateur qui permettait de faire tout fonctionner ensemble, ou même d'un potentiel modèle épidémique qui pourrait être ajouté un jour. On remarque donc que réaliser cette simulation en partant de rien nous demanderait un effort titanesque, d'où l'intérêt que nous portons pour le travail de Dustin Carlino qui est un outil déjà très abouti au niveau des fonctionnalités disponibles.

\pagebreak

### Le simulteur A/B Street

Dustin Carlino est cartographe spéculatif. Il a pour mission de cartographier des données qui ne l'ont pas encore été ou qui ne le sont que partiellement. C'est le cas des déplacements des gens au sein d'une ville qui peuvent être simulés en utilisant différentes cartes. Avant de créer son projet, Dustin Carlino était un software developer chez Google à Seattle. Depuis 2018, il travaille sur A/B Street [@abstreet], un jeu sérieux permettant de simuler le trafic routier comprenant les bus, les voitures, les vélos et les piétons. Ce simulateur, développé en Rust, est open-source et disponible depuis la plateforme [Github](www.abstreet.org).

Il a pour objectif de nous permettre d'interagir avec les routes et la signalisation en y ajoutant, par exemple, des lignes de bus ou de vélo, mais également en retirant des places de parking ou en modifiant un croisement afin de rediriger le trafic. N'importe quel utilisateur peut alors observer les influences de ses modifications sur la topologie du réseau routier et comprendre comment évoluent les déplacements des gens.

A/B Street a été créé dans le but de mettre en avant des moyens de transport plus respectueux de l'environnement comme le vélo. De plus, il vise aussi à trouver des solutions pour désengorger le trafic, notamment celui généré par les mobilités pendulaires, en proposant des solutions alternatives et réalisables sur le réseau routier existant. Par exemple, il est possible de modifier une route afin d'y ajouter une voie de bus et d'observer le comportement qui en découle. Si les changements sont bénéfiques, nous pouvons même nous questionner sur la faisabilité réelle d'un changement sur une route.

Ce simulateur est composé de différents modules qui assurent son bon fonctionnement. Nous allons évoquer, ici, deux exemples de modules qui permettent de faire la simulation des déplacements correctement, mais qui ne sont pas directement liés aux transports en commun.

### La technologie Open Street Map

Basé sur la ville de Seattle dans un premier temps, A/B Street s'est aujourd'hui ouvert au reste du monde grâce à son utilisation de la technologie (+OSM_a). C'est un projet collaboratif de cartographie en ligne qui permet de créer des cartes sous une licence libre en utilisant le système GPS et d'autres données libres comme des photographies aériennes ou de simples informations sur la connaissance du terrain.

\pagebreak

N'importe quel utilisateur de (+OSM_a) peut proposer des modifications sur une route, un bâtiment, une intersection... Afin de rendre la carte plus précise pour les autres utilisateurs. En quelques exemples succincts (+OSM_a) permet l'ajout et la modification de la signalisation routière (panneaux, feux, passages piétons...), des différentes routes et axes de transports (ronds-points, autoroutes, voies exclusives aux bus...), des trottoirs, mais également des habitations, des infrastructures (gares, aéroports...) pour fournir une carte avec un maximum de détails. Voici un exemple de ce qu'il est possible de faire depuis le site d'Open Street Map [@openstreetmap]:

\cimg{figs/osm_edition.png}{width=\textwidth}{Interface d'édition d'une route sur OSM}{Source : \url{www.openstreetmap.org}, ref. URL10}

Sur la figure 1.1, on voit qu'il est possible de modifier le nom de la route, d'indiquer si elle est à sens unique ou non, de choisir la limite de vitesse autorisée... Comme on peut le voir, (+OSM_a) est un outil qui est donc très complet et qui permet à n'importe quel utilisateur d'apporter des modifications sur le contenu actuel.

Dans le cadre de A/B Street, le fait d'utiliser (+OSM_a) permet de créer une simulation pour n'importe quelle ville cartographiée avec ce même outils comme c'est le cas pour Genève. C'est le fruit d'années de travail et de collaboration de volontaires qui alimentent encore aujourd'hui la carte de la ville avec des nouvelles informations ou apportent des corrections.

Le simulateur peut importer n'importe quelle carte de ville et s'en sert comme base pour modéliser le trafic routier. Étant donné qu'il est possible d'apporter des modifications à la carte, il n'est pas vraiment possible de garantir une précision maximale sur les cartes qui peuvent comporter des erreurs ou des imprécisions.

### La simulation du trafic routier

En plus de la carte qui est le module de base de la simulation, A/B Street est composé d'une multitude d'autres modules comme la simulation du trafic routier. Si (+OSM_a) permet de créer une carte très complète, il est indispensable qu'un module de l'application permette de créer et gérer le trafic généré par les bus, les voitures, les vélos et les piétons en se basant sur la carte sélectionnée.

D'après la documentation officielle de A/B Street [@abstreet], cette logique va se baser sur une horloge afin de générer du trafic lorsqu'il est nécessaire. À titre d'exemple, on souhaite que beaucoup de monde prenne leur voiture à 8 h 00 et à 17 h 00, mais que le trafic soit fluide voir presque inexistant en pleine nuit. Néanmoins, la compréhension de ce point n'est pas nécessaire pour la suite du projet, il sert surtout à comprendre comment fonctionne le simulateur et ne sera pas développé par la suite.

Cette gestion du trafic est appelée une simulation à événements discrets. Un scénario est utilisé pour gérer des événements qui se greffent à la succession des tâches en cours (comme changer l'état d'un feu de signalisation, se garer ou encore passer le temps). Il existe une multitude d'états comme l'arrivée d'une voiture à un feu rouge ou la prise en compte des voitures aux alentours qui empêchent un bus de tourner.

Prenons le cas du pont du Mont-Blanc en plein centre-ville de Genève :

\cimg{figs/pont-mont-blanc1.png}{scale=0.2}{Trafic routier au pont du Mont Blanc (à 7h42)}{Source : image tirée de A/B Street disponible sur \url{abstreet.org}, ref. URL01}

Ce que nous pouvons dire à partir de la figure 1.2, c'est que le trafic est particulièrement chargé le matin, ce qui semble tout à fait cohérent avec la réalité.

\pagebreak

\cimg{figs/pont-mont-blanc2.png}{scale=0.2}{Trafic routier au pont du Mont Blanc (à 7h41)}{Source : image tirée de A/B Street disponible sur \url{abstreet.org}, ref. URL01}

Sur la figure 1.3 qui correspond à un zoom de la première illustration, nous observons davantage de détails sur le trafic actuel et les intersections qui créent des engorgements sur le pont. Ce que nous pouvons égallement remarquer, c'est qu'il manquent les bus dans la simulation actuelle.

Tous ces déplacements sont orchestré à travers un scénario. C'est ce dernier qui va être à l'origine du déplacement d'une personne pour une raison précise, à une heure quelquonque avec un moyen de transport adapté. Il est donc crucial pour la simulation des déplacements des gens. Ceci est le travail de Ilias N'hairi [@nhairi_project] qui a besoin de la modélisation des transports en communs pour pouvoir réaliser un scénario cohérent avec la mobilité genevoise.

\pagebreak

## La structure de données General Transit Feed Specification

En introduisant A/B Street, nous avons évoqué les différents moyens de transport disponibles en rappelant que la simulation ne tient pas encore compte des transports en commun pour la ville de Genève. Il y a donc un travail d'import à faire qui implique de bien comprendre la manière dont les (+TPG_a) sont représentés dans une structure de données.

### Description du format

Aujourd'hui, la manière la plus efficace de représenter les transports en commun est d'utiliser une structure de données (+GTFS_a). C'est un format informatique standardisé, développé par Google et TriMet qui permet de communiquer des horaires de transports en commun et les informations géographiques associées (topographie d'un réseau, emplacement des arrêts, tracés des lignes, horaires de passage...).

Nous utilisons le format (+GTFS_a) Static qui s'oppose au format (+GTFS_a) Realtime fournissant des données en temps réel (ce dont nous n'avons pour l'instant pas besoin). On pourrait résumer cette structure de données comme un dossier contenant des fichiers qui interagissent entre eux en partageant des données comme des numéros de ligne. Chaque fichier fournit des informations sur un aspect spécifique tel que les arrêts (`stops.txt`), les itinéraires (`routes.txt`), les trajets quotidiens (`trips.txt`), les sociétés de transport (`agency.txt`) et d'autres données relatives aux horaires. Certaines informations sont nécessaires pour fournir des données GTFS valides, d'autres sont facultatives et fournissent des informations supplémentaires comme les changements d'horaires sur des jours fériés (`calendar_dates.txt`).

### Les données publiques sur la mobilité en suisse

Pour la ville de Genève, actuellement, une structure de données (+GTFS_a) est mise à jour chaque année sur la plateforme des données publiques pour la mobilité en Suisse [@le_site_des_gtfs]. Notamment fournie par les (+CFF_a) elle rassemble dans un même (+GTFS_a) toutes les sociétés de transports suisses dont les (+TPG_a).

Le graphique suivant montre les interactions entre les différents fichiers présents dans ce set de données (+GTFS_a). Il n'est pas nécessaire de comprendre ce graphique, mais plutôt de visualiser l'interdépendance des fichiers qui est matérialisée par les flèches afin de voir que les fichiers partagent tous des données entre eux.

\pagebreak

\cimg{figs/gtfs_static.png}{scale=0.4}{Diagramme de relations entre les fichiers d'un GTFS fourni par La plateforme des données publiques pour la mobilité en Suisse}{Source : \url{opentransportdata.swiss}, ref. URL02}

Il est important de noter que ce graphique de la figure 1.5 montre tous les fichiers qui peuvent faire partie d'une structure (+GTFS_a). Dans notre cas, nous nous contenterons du strict minimum permettant de modéliser les transports en commun, c'est-à-dire les routes (ou lignes) qui composent les (+TPG_a) ainsi que tous les trajets de toutes les routes, leurs arrêts, l'ordre de succession de ces derniers en fonction des trajets et leurs horaires de passages. Ceci ne constitue donc que six fichiers parmis les douze possibles (`agency.txt`, `routes.txt`, `trips.txt`, `stops.txt`, `shapes.txt` et `stop_times.txt`).

Pour revenir sur le contenu du set (+GTFS_a) fourni, il faut rappeler que toutes les sociétés de transports suisses y sont présentes. Avant d'importer les données, il y a donc un réel travail de tri à faire afin d'isoler les (+TPG_a) du reste des sociétés.

\pagebreak

## Des données publiques incomplètes

Après un premier travail sur le set de données, nous avons remarqué que les données (+GTFS_a) transmises par la plateforme des données publiques pour la mobilité en Suisse étaient incomplètes. Il manque, par exemple un fichier entier (`shapes.txt`) et des données cruciales dans le fichier `stops.txt`. Pour avoir un résultat satisfaisant dans notre simulation, il nous est alors indispensable de coupler les données des (+CFF_a) avec d'autres acteurs.

### Les Systèmes d'Information du Territoire à Genève

Afin d'apporter des modifications au set de données (+GTFS_a) initial, nous avons besoin des informations des (+SITG_a). Ces derniers se décrivent comme : « Un organisme fondé sur un réseau de partenaires publics ayant pour but de coordonner, centraliser et diffuser largement les données relatives au territoire genevois. Les partenaires partageant entre eux et avec un large public les données géographiques produites dans le cadre de leurs missions »[^4]. Cet organisme dispose de données très précises sur le canton de Genève, notamment en rapport avec les (+TPG_a) dont nous avons grandement besoin. Il est possible de visualiser, par exemple, une partie de la ville en 3D avec la technologie lidar :

\cimg{figs/sitg_3d.png}{scale=0.2}{Représentation du carrefour de la Prairie en 3D avec la technologie Lidar fournie par les SITG}{Source : \url{sitg.maps.arcgis.com/apps/webappviewer3d/index.html}, ref. URL011}

\pagebreak

Mais ce qui est vraiment intéressant pour nous, c'est le recensement des données relatives aux (+TPG_a) comme l'emplacement des arrêts :

\cimg{figs/sitg_arrets.png}{scale=0.3}{Carte des SITG montrant l'emplacement des arrêts des TPG dans le centre de Genève}{Source : \url{map.sitg.ch/app}, ref. URL011}

Avec la figure 1.7 on remarque que les (+SITG_a) peuvent nous être d'une grande aide afin de réaliser une simulation précise. Nous allons donc voir quelles sont les étapes nécessaires afin d'importer le réseau de transports en commun pour le canton de Genève dans A/B Street.

[^4]: Disponible à l'adresse: \url{ge.ch/sitg/le-sitg}

\pagebreak
