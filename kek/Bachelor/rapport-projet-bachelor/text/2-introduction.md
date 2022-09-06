\pagenumbering{arabic}

# Introduction {-}

La mobilité dans le canton de Genève a beaucoup évolué depuis vingt ans. D'après une étude menée par l'Office Cantonal de la statistique[^1] datée de 2019 [@la_mobilite_des_habitants_du_canton_de_geneve], les personnes se déplaçant dans le canton de Genève pour travailler n'utilisent la voiture plus que dans 30 % des cas en 2015 contre 53 % en 2000. Ceci est dû à l'essor de nouveaux moyens de transport plus respectueux de l'environnement comme le vélo, mais également grâce au réseau de transports en commun qui couvre tout le canton de Genève et la France voisine. Dans le cadre de notre projet de bachelor à la (+HEPIA_a), il semble très intéressant de modéliser les déplacements des gens dans le canton de Genève pour aider à la planification urbaine.

En effet, ceci pourrait permettre d'identifier des axes de transports qui sont souvent engorgés, des routes où il manquerait des voies de bus, mais également et surtout des pistes cyclables à rajouter. Outre le fait de contribuer à l'organisation du réseau routier, ce travail pourrait aussi permettre d'aider à modéliser des phénomènes très différents tels que la propagation d'une épidémie. Si nous savons aujourd'hui que nous n'étions pas suffisamment préparés pour faire face au Covid-19, comprendre comment et où se diffuse un virus permettrait d'en apprendre davantage sur les schémas de transmission d'un futur virus et les potentielles zones à risque de contamination comme les transports en commun.

À titre d'exemple, ces derniers permettaient déjà à 611'000 voyageurs quotidiens de se déplacer dans le canton de Genève en 2019 d'après le Rapport Annuel de Gestion des (+TPG_a)[^2] daté de 2020 [@le_rapport_des_tpg]. Ce nombre a cependant, fortement diminué pour passer à 404'000 en 2020 à cause de la pandémie. En nous appuyant sur les chiffres de ce rapport, il semble donc évident que les (+TPG_a) jouent un rôle majeur dans la mobilité au sein du canton Genève.

[^1]: Disponible à l'adresse: \url{statistique.ge.ch/tel/publications/2019/analyses/communications/an-cs-2019-59.pdf}
[^2]: Disponible à l'adresse: \url{tpg.ch/sites/default/files/2021-07/TPG-RAG2020_WEB_pageparpage_FINAL.pdf}

\pagebreak

Nous pourrions alors nous demander dans quelle mesure il serait possible de modéliser le réseau des (+TPG_a) afin de l'utiliser pour simuler et étudier les déplacements quotidiens des gens.

Pour réaliser ce travail de bachelor, nous nous basons sur le projet de Dustin Carlino. Depuis 2018, il développe en Rust un simulateur de trafic routier. Afin d'intégrer ces données, il est nécéssaire d'étudier la structure de données utilisée pour décrire les (+TPG_a) [@doc_google_gtfs] . La majeur partie de ce projet concerne le nettoyage des données publiques utilisée safin d'exploiter pleinement ces informations dans le simulateur. Cela commence par la collecte des données fournies librement par la Plateforme des données publiques pour la mobilité en Suisse [@le_site_des_gtfs] et va jusqu'aux modifications du set de données à l'aide d'outils externes comme le (+SITG_a) [@le_site_des_sitg]. Enfin, dès lors que le set de données et cohérent et importé dans le simulateur, nous utilisons (+OSM_a),un outil de cartographie collaboratif [@openstreetmap], pour affiner nos résultats avant de mesurer la qualité de notre import du réseau des (+TPG_a).

Ce rapport se divise en trois parties majeures. La première sera une analyse théorique de la situation actuelle où nous verrons le fonctionnement de A/B Street et décrirons les différents acteurs et outils qui ont permis de réaliser ce travail. De plus, nous évoquerons également le fonctionnement de la structure de données utilisée pour représenter les transports en commun. La seconde partie sera consacrée à la description du procédé permettant d'obtenir un set de données pour les (+TPG_a). Nous illustrerons les étapes qui auront été nécessaires afin de reproduire le plus fidèlement possible, le réseaux des (+TPG_a) dans le jeu sérieux. Dans une troisième partie, nous reviendrons sur les résultats en mesurant la fiabilité de l'import réalisé. Pour ce faire, nous utiliserons le travail de Ilias N'hairi [@nhairi] réalisé en parallèle sur le même simulateur. Ayant pour objectif de répartir la population et de reproduire avec précision les déplacements des gens, c'est un travail de bachelor qui est directement lié à ce projet. Nous utiliserons donc ses données et son travail afin d'effectuer diverses mesures permettant d'étudier la fiabilité du réseau des (+TPG_a) importé dans A/B Street.

L’intégralité du code, des fichiers et des données utilisées pour ce projet sont disponibles sur le projet Github[^3] de ce travail de bachelor.

[^3]: Disponible à l'adresse: \url{github.com/thomasdgr/abstreet}

\pagebreak
