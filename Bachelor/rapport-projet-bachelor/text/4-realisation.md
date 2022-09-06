# Réalisations

## L'analyse des données GTFS

À travers cette première introduction à la structure de données (+GTFS_a), nous avons vu que la plateforme des données publiques pour la mobilité en Suisse  [@le_site_des_gtfs] propose un set de données de ce type fourni par les (+CFF_a). Ce set comprend cependant, toutes les sociétés de transports suisses et non pas seulement les (+TPG_a). Une première partie consiste donc à réaliser un analyseur de données afin d'isoler le contenu des (+TPG_a) de celui des autres agences de transports suisses.

### Approche pratique

Étant donné que le projet A/B Street est réalisé en Rust, une bonne manière de se familiariser avec le langage avant de prendre en main le simulateur est de réaliser ce programme en Rust. Pour la réalisation de ce programme et l'apprentissage du langage, il a été nécessaire d'utiliser le livre The Rust Programming Language écrit par Steve Klabnik et Carol Nichols et paru en 2018 [@le_bouquin_de_rust]. Cet outil indispensable à l'apprentissage du Rust a été complété par les cours du Docteur (+OPM_a) [@malaspinas] et différents sites web.

### Description du travail à réaliser

Lors de la présentation des (+GTFS_a) nous avons vu que les fichiers qui composent cette structure de données sont interdépendants. Prenons un exemple simple tiré du fichier `agency.txt` disponible sur la plateforme des données publiques pour la mobilité en Suisse [@le_site_des_gtfs]:

```md
1. agency_id, agency_name, agency_url, ...
2. "11", "Schweizerische Bundesbahnen SBB", "sbb.ch", ...
3. "86", "Zentralbahn", "sbb.ch", ...
4. "881", "Transports Publics Genevois", "sbb.ch", ...
5. "151", "Transports Publics de la région Lausanoise", "sbb.ch", ...
```

Ci-dessus, nous voyons un court extrait de ce dont est composé le fichier `agency.txt`. Ce fichier répertorie l'ensemble des 458 agences de transports suisses.

Maintenant, voyons à quoi ressemble le contenu du fichier `routes.txt` qui répertorie l'ensemble des lignes de toutes les agences précédemment évoquées (soient 4486 dont 76 pour les (+TPG_a)):

```md
1. route_id, agency_id, route_short_name, ..., route_type
2. "91-10-A-j22-1", "37", "10", ..., "900"
3. "91-10-B-j22-1", "78", "s8", ..., "300"
4. "91-12-j22-1", "881", "12", ..., "900"
5. "91-14-j22-1", "881", "14", ..., "900"
```

Ce fichier est également disponible sur la plateforme des données publiques pour la mobilité en Suisse [@le_site_des_gtfs]. On remarque que, dans les deux fichiers, un champ `agency_id` est présent. Dans le premier fichier, le `agency_id` "881" est l'identifiant unique de l'agence des (+TPG_a). Dans le second fichier, nous retrouvons également la valeur "881" pour le champ `agency_id`. Mais cette fois-ci, c'est pour identifier à quelle agence correspond à la route (ou ligne de bus) actuelle. Puisque ce fichier représente toutes les lignes de toutes les agences, on en déduit que les deux lignes mises en évidence montrent les lignes de tramways 12 et 14 des (+TPG_a).

Notre objectif avec ce set de données (+GTFS_a) est d'isoler les données qui concernent les (+TPG_a). L'exemple précédent permet de monter la démarche à suivre pour isoler les données des (+TPG_a) du reste des agences de transport suisses. L'approche évoquée est la même pour chacun des fichiers sauf qu'au lieu d'utiliser le champ `agency_id`, nous pourrions utiliser le champ `route_id` pour isoler tous les trajets de toutes les lignes des (+TPG_a) dans le fichier `trips.txt`.

\pagebreak

### Description du fonctionnement

À partir de la rapide explication du point précédent, voici le flux d'exécution du programme :

\cimg{figs/workflow.png}{width=\textwidth}{flux d'éxécution du programme pour les trois premiers fichiers de la structure GTFS}{}

La figure 2.1 permet de décrire la manière d'isoler les données des (+TPG_a). La partie à droite de l'image, qui n'est pas remplie, sert à montrer que certains champs du fichier `trips.txt` permettent d'isoler les données des autres fichiers de la structure (+GTFS_a) comme `stops.txt` ou `stop_times.txt`.

### Le fichier shapes.txt

En partant de la structure de données globale, nous avons donc une nouvelle structure de données qui contient uniquement les informations relatives aux (+TPG_a). Pour rappel, nous avions évoqué plus tôt, lors de la présentation de la structure (+GTFS_a), que certains fichiers étaient facultatifs. Le fichier `shapes.txt` est noté comme indispensable selon la documentation de google, mais est pourtant absent dans le set de données fourni par la plateforme des données publiques pour la mobilité en Suisse  [@le_site_des_gtfs]. Ce nouveau fichier permet de décrire, pour un trajet donné, l'ordre dans lequel se suivent les arrêts du point de départ au terminus.

\pagebreak

Le souci avec ce fichier manquant, c'est qu'il devient alors impossible de savoir quels arrêts se succèdent lors d'un trajet et dans quel sens. Il est alors indispensable de le créer à la main. Par exemple, si nous prenons le cas de la ligne 19 des (+TPG_a), voici un extrait du tracé du trajet quotidien :

\cimg{figs/ligne_19_reel_zoom.png}{width=\textwidth}{Extrait du tracé du trajet quotidien de la ligne 19}{Source : \url{moovitapp.com}, ref. URL03}

Sans le fichier `shapes.txt`, il nous est impossible de trouver les points qui décrivent le trajet emprunté par le bus 19 qui est montré sur la figure 2.2. Il nous faut donc, pour ce tracé, mais aussi pour tous les tracés des lignes des (+TPG_a), un moyen de trouver les arrêts qui composent un trajet, leurs coordonnées et la distance parcourue depuis le début du trajet afin de déterminer la route à prendre.

Dans notre cas, grâce au travail de Dustin Carlino pour simuler les déplacements des gens, nous n'avons pas besoin de calculer la distance, car il utilise une version de l'algorithme du plus cours chemin de Dijkstra dont les spécifications sont décrites sur son guide de A/B Street[^5].

[^5]: Disponible à l'adresse: \url{a-b-street.github.io/docs/software/ungap_the_map/tech_details.html}

\pagebreak

C'est un autre module dont nous avons la chance de bénéficier et qui nous fait gagner beaucoup de temps dans la création de ce fichier.

Cependant, nous devons tout de même construire ce fichier à la main en identifiant les arrêts, l'ordre dans lequel ils se succèdent et leurs coordonnées. Pour récuperer la séquence de succession des arrêts, on peut utiliser le fichier `stoptimes.txt`. Pour un trajet, il donne les heures de passage à chacun des arrêts. ON peut donc savoir dans quel ordre se succèdent les arrêts d'un trajet d'une ligne. Ensuite, nous devons faire le lien entre les arrêts et le fichier `stops.txt` pour identifier les coordonnées de chaque arrêt de la séquence d'un trajet. Ensuite, on rassemble toutes les données dans une même structure `Shape` que l'on inscrit dans le fichier `shapes.txt`.

Une fois ce fichier créé à partir des données fournies par la structure (+GTFS_a), il est alors possible de commencer l'import des données dans A/B Street.

## Un set de données incomplet

Précédemment, nous évoquions le fait que le set de données (+GTFS_a) initial était incomplet. Si nous sommes en mesure de créer le fichier `shapes.txt` manquant, ce n'est malheureusement pas le cas de certaines autres informations contenues dans cette structure de données.

### Le fichier stops.txt

Ce fichier indique l'emplacement des arrêts grâce aux coordonnées GPS. Dans A/B Street, l'arrêt est placé sur un trottoir afin que les bus puissent desservir les passagers comme c'est le cas réellement. Il est aussi important de savoir que, la plupart du temps, il existe au moins deux arrêts qui portent le même nom (un arrêt pour le sens aller et un pour le sens retour).

Le souci avec les données transmises par la plateforme des données publiques pour la mobilité en Suisse [@le_site_des_gtfs], c'est qu'aucune distinction n'est faite entre les arrêts qui portent le même nom. Encore pire, il n'existe qu'une seule variation d'un arrêt dans le fichier. Prenons l'arrêt `Bel-Air` par exemple. D'après le site des TPG [@le_site_des_tpg], il n'y a pas moins de 13 lignes qui passent par un arrêt `Bel-Air` dans les deux sens.

Sans prendre en compte le fait qu'il existe un sens aller et un sens retour, supposons simplement que nos 13 lignes passent par un seul et même arrêt. Le fichier `stops.txt` censé contenir le nom et les coordonnées GPS de chacun des arrêts ne contient donc qu'une fois l'arrêt `Bel-Air`. Voyons alors l'effet que cela a sur la simulation avec le plan des connexions pour cet arrêt :

\pagebreak

\cimg{figs/bel_air_arrets_tpg.png}{scale=0.3}{Plan de connexion de l'arrêt Bel-Air}{Source : \url{tpg.ch}, ref. URL08}

Nous constatons avec ce plan de la figure 2.3 qu'il existe en réalité, plusieurs arrêts `Bel-Air` matérialisés par les lettres `A` à `G`. Or, dans notre cas, il n'en existe qu'un seul. La conséquence de cette situation est que toutes les lignes qui passent par cet arrêt doivent passer par le même point exact (en l'occurrence, le point B sur la figure précédente). Cela cause donc des détours dans les trajets des lignes comme nous pouvons le voir sur l'image suivante :

\cimg{figs/ligne_17_bel_air.png}{scale=0.3}{Comparaison du tracé réel de la ligne 17 tirée de moovitap.com et du tracé de la ligne 17 dans A/B Street}{Source : Thomas Dagier}

\pagebreak

Avec cette comparaison, on remarque que nous perdons beaucoup en précision à juste nous contenter des données du set (+GTFS_a) initial. C'est pourquoi nous devons passer par d'autres sources d'informations.

À notre connaissance, et comme évoqué plus tôt, nous pouvons tirer des données soit de (+OSM_a), soit des (+SITG_a). Après quelques recherches, il semble bien trop compliqué d'obtenir des données uniquement sur les (+TPG_a) grâce à (+OSM_a) du fait qu'elles ne sont pas triées pour être utilisables de la sorte. Les (+SITG_a), en revanche, proposent un set de données contenant tous les arrêts et leurs dérivations dans un format assez similaire à celui que nous connaissons déjà avec les (+TPG_a).

Le format (+KML_a) permet de représenter des entités géographiques dans des applications telles que Google Earth. La force de ce set de données, en plus de contenir tous les arrêts, est qu'il contient la direction relative aux arrêts par lesquels les lignes passent. Voici un exemple de données contenu dans ce fichier :

```md
<table>
    <tr>
        <td>6.143444023611796,46.2048626076406,0</td>
        <td>Bel-Air</td>
        <td>18,14</td>
        <td>18,14 (18 (CERN),14 (Meyrin-Gravière))</td>
    </tr>
</table>
```

Ici, on a plusieurs informations intéressantes. La première, c'est que nous connaissons les coordonnées d'une dérivation de l'arrêt `Bel-Air` (le point A sur la figure 2.3). On peut donc être beaucoup plus précis. La seconde, c'est que nous possédons la direction. On sait donc que cet arrêt `Bel-Air` doit être dans la séquence (entrée du fichier `shapes.txt`) de la ligne 14 et la ligne 18 lorsqu'elles se dirigent respectivement vers le `Meyrin-Gravière` ete vers le `CERN`.

Une partie importante du travail est donc d'extraire ces informations venant des (+SITG_a) et les coupler avec celles venant du set (+GTFS_a). Cette étape est indispensable, car chaque arrêt du set (+GTFS_a) possède un identifiant unique qui est réutilisé dans les autres fichiers comme `stoptimes.txt` dont on discutera plus tard.

Dans les données des (+SITG_a) il n'y a évidemment pas cet identifiant, car les données sont tirées de deux sources différentes.

\pagebreak

Le couplage est une partie complexe du travail puisque le seul lien entre les deux sets de données est le nom des arrêts. Souvent, ces derniers varient quelque peu, ce qui nous impose de devoir faire de la reconnaissance de motifs. Par exemple, l'arrêt `Léonard Sismondi` de la ligne 15 est inscrit tel quel dans le set de données des (+SITG_a) alors qu'il est inscrit `L.-Sismondi` dans celui des (+GTFS_a). Pour ceci, nous utilisons différentes techniques comme la distance de Levenstein [^6] ou un algorithme de recherche approximative (Fuzzy Search Algorithm[^7]).

Sans rentrer dans les détails de ces algorithmes qui n'ont pas été ré-implémenté, on pourrait simplement dire que la distance de Levenstein entre deux chaînes de caractères permet de mesurer le nombre de lettres d'une première chaîne qu'il faudrait enlever, ajouter ou remplacer pour obtenir la seconde. Si notre distance est faible, c'est que nous avons une correspondance entre le nom d'un arrêt du set des (+SITG_a) et celui des (+GTFS_a).

C'est une très bonne première approche pour filtrer les arrêts qui ont le même nom ou presque (comme `Meyrin-Gravière` et `Meyrin Graviere`) et ne garder que ceux pour lesquels il y a une vraie différence (comme l'arrêt `L.-Sismondi`). Pour trouver une correspondance avec les arrêts restant la distance ne suffisant pas, nous avons besoin d'un algorithme de reconnaissance de motifs. Le Fuzzy Search (ou recherche approximative) permet d'identifier des chaînes de caractères qui se ressemblent approximativement. À partir d'un motif, qui serait la chaîne de caractère du set des (+SITG_a) à faire correspondre, nous mettons un poids à chaque correspondance et on conserve le poids le plus fort (qui correspond à la chaîne qui a la plus de chance d'être celle que nous cherchons).

Cet algorithme est très efficace quand il y a peu de ressemblances entre les différentes options. C'est le cas ici puisque, dans le set des (+GTFS_a), on a un seul arrêt et pas les dérivations. Pour l'arrêt `Gare Cornavin`, comme il n'existe qu'en une fois dans le set (+GTFS_a), nous avons peu de chances d'avoir deux ressemblances avec un poids élevé dans le set des (+SITG_a).

Au départ, dans le set des (+GTFS_a) nous avions 867 arrêts. Dans le set des (+SITG_a) nous avons 1902 arrêts. Après application de ces deux algorithmes, on filtre correctement 1891 arrêts, soit 99.4 %. Le reste est malheureusement modifié à la main, soit, car aucune ressemblance n'a été trouvée, soit, car une ressemblance a été trouvée, mais ce n'est pas celle attendue. Voici un exemple d'arrêt non importé avec le nom dans les (+SITG_a): `Aire-la-Ville-Pont-de-Peney` et le nom dans le set des (+GTFS_a): `A. la vile` (la faute d'orthographe est vraiment dans le set).

[^6]: Disponible à l'adresse: \url{fr-academic.com/dic.nsf/frwiki/520675}
[^7]: Disponible à l'adresse: \url{nanonets.com/blog/fuzzy-matching-fuzzy-logic}

\pagebreak

### Isoler une petite partie des données

Une fois cette étape réalisée et le set de données bien plus précis, il est nécessaire de filtrer les données intéressantes pour les utiliser dans A/B Street. Le set de données des (+GTFS_a) décris tous les trajets de toutes les lignes des (+TPG_a). On peut donc connaître le trajet que fait la ligne 26 lorsqu'elle se déplace à 5 h 12 du dépôt vers le point de départ de la ligne ou même les trajets de la ligne 08 qui ne sont fait qu'une fois par jour. Ce qui nous intéresse vraiment, ce sont les trajets des lignes qui sont les plus récurrents. Pour ce faire, nous partons du principe que les trajets récurrents sont ceux qui passent entre 11 h 00 et 16 h 00. Ensuite, on fait une recherche pour savoir quels sont les trajets les plus longs et qui comportent le même nombre d'arrêts (à deux près). Ceci nous permet d'isoler le trajet récurent dans le sens aller et celui dans le sens retour.

Cette partie du travail qui est assez rapide nous a permis d'identifier un problème. Une séquence d'arrêt (dans `stoptimes.txt`) décrit, pour un trajet donné, l'ordre de succession des arrêts et l'horaire de passage. Un arrêt est décrit par son identifiant unique qui peut être retrouvé dans le fichier `stops.txt` (d'où la volonté de faire correspondre le set des (+SITG_a) et celui des (+GTFS_a)). Le souci avec cette méthode, c'est qu'après l'étape de correspondance des arrêts, les identifiants ne sont plus du tout unique. Prenons un exemple :

```md
1. trip_id, departure_time, arival_time, stop_id, stop_sequence
2. "895.TA.91-15-j22-1.11.R","15:16:00","15:16:00","8587058",1
3. "895.TA.91-15-j22-1.11.R","15:17:00","15:17:00","8592905",2
4. "895.TA.91-15-j22-1.11.R","15:18:00","15:18:00","8592825",3
```

Sur cet extrait du fichier `stoptimes.txt` qui décrit l'ordre de succession des trois premiers arrêts d'un trajet de la ligne 15, nous remarquons la présence d'un `stop_id` qui est l'identifiant unique d'un arrêt. L'identifiant `8587058` correspond à l'arrêt `Nations`. Dès lors que nous avons couplé les données, il n'y a plus un seul arrêt `Nations` comme avant, mais huit. Le souci avec cela, c'est qu'en ajoutant des arrêts dans `stops.txt`, nous devons aussi refaire tous les trajets en prenant à chaque fois le bon arrêt `Nations` parmi tous ceux possibles.

La première étape est de garder le concept d'identifiant unique. Tous les identifiants pour l'arrêt `Nations` auront donc un identifiant semblable à `8587058-X` en modifiant `X` pour chaque dérivation de l'arrêt.

\pagebreak

Ensuite, nous devons trouver le bon arrêt `Nations` parmi tous ceux disponibles. Voici un exemple de ce que contient le fichier `stops.txt`:

```md
1. stop_id,stop_name,stop_lat,stop_lon,routes
2. 8587058-1,"Nations",46.22263,6.13911,"F(Gare Cornavin), 20(Place de Neuve)"
3. ...
4. 8587058-3,"Nations",46.22218,6.13905,"15(Grand-Lancy-Place du 1er-Août)"
```

Avec cet extrait, on observe deux variantes de l'arrêt `Nations`. Le champ `routes`, extrait du format (+KML_a), nous permet d'identifier pour quel trajet l'arrêt est utilisé. Pour savoir quel arrêt est le bon, nous devons regarder, pour le trajet `895.TA.91-15-j22-1.11.R` (tiré de l'extrait du fichier `stoptimes.txt`) quel est le terminus et le comparer avec les données du champ `routes`.

Voici un extrait du fichier `trips.txt`:

```md
1. route_id,trip_id,trip_headsign,trip_short_name,direction_id
2. "91-12-j22-1","903.TA.91-12-j22-1.7.R","Lancy-Bachet"," gare","0"
3. "91-14-j22-2","1058.TA.91-14-j22-1.6.R","Bernex"," Vailly","1"
4. "91-15-j22-1","895.TA.91-15-j22-1.11.R","Grand-Lancy"," Place du 1er-Août","0"
```

On retrouve dans ce fichier l'identifiant du trajet extrait du fichier `stoptimes.txt`. Avec cet identifiant, nous observons aussi que la destination de ce trajet est `Grand-Lancy Place du 1er-Août`. En nous aidant de cette information et du champ `routes`, on peut identifier quel est l'arrêt `Nations` à sélectionner parmi tous les doublons existants. Pour faire cette correspondance, on peut, de nouveau, utiliser l'algorithme de recherche approximative en affinant un peu les recherches. En effet, on peut déjà trier les arrêts en fonction des lignes qui sont desservies. Par exemple l'arrêt possédant l'identifiant `8587058-1` n'est pas utilisé par la ligne 15 donc il est possible de retirer cet arrêt des choix potentiels. Ensuite, pour les arrêts restant, nous pouvons réutiliser l'algorithme de recherche approximative pour affiner davantage les arrêts et n'en garder qu'un seul.

Nous réalisons cette étape pour chacun des arrêts de chacun des trajets afin d'avoir les bons arrêts en fonction des trajets pour toutes les lignes.

### Genève, un cas à part

Genève a la particularité d'être un territoire situé à la frontière d'un autre pays. Ce n'est pas souvent le cas dans (OSM_a) et cela peut causer de gros problèmes dans A/B Street. En effet, le simulateur utilise un outil nommé Geofabrik[^8] qui permet d'extraire les données d'(+OSM_a) selon un polygone de coordonnées spécifiques. Le souci avec cet outil est qu'il n'est pas possible d'importer des données de plusieurs pays en même temps.

\pagebreak

Après avoir posé la question à Dustin Carlino, cela pourrait être un projet à part entière tant le travail est complexe. Pour importer des données, on renseigne donc un polygone (dans notre cas un carré avec des coordonnées pour chaque angle) et nous importons toutes les données qui se situent dans ce carré. Puisque nous n'importons que des données suisses pour la carte, il y aura donc un problème avec les lignes et les arrêts qui sont en France. Par exemple, à partir d'un polygone englobant Genève et la France voisine, nous devrions être en mesure de simuler le passage d'une en France. Cependant, comme les données françaises de (+OSM_a) ne sont pas importées, il est impossible de modéliser les routes du côté français et donc d'importer ces lignes.

Pour régler ce problème, il suffit de lister tous les arrêts qui sont en France en utilisant leurs coordonnées GPS et en regardant si elles sont en Suisse. Ainsi, on ne conserve que les données suisses et nous pouvons aussi savoir quelles lignes sont exclusivement en France comme le bus N ou quelles lignes sont partiellement en France comme le bus M et F. Dans ce cas, on raccourci la ligne afin que le point de départ ou d'arrivée de la ligne soit le dernier arrêt avant la frontière avec la France :

\cimg{figs/ligne_f_comparaison.png}{scale=0.3}{Comparaison du tracé de la ligne F dans de A/B Street et du tracé de la ligne F tiré des SITG}{Source : Thomas Dagier}

On observe alors que la ligne F est stoppée après la douane et ne continue pas en direction de Gex comme c'est le cas réellement d'après les (+SITG_a).

\pagebreak

Il existe cependant des cas spéciaux comme le montre le bus M :

\cimg{figs/bus_M_sitg.png}{scale=0.3}{Tracé de la ligne M coté suisse}{Source : \url{sitg.ch}, ref. URL11}

Sur la figure 2.6, on observe que le bus M possède un seul arrêt du coté Suisse. On doit donc affiner le filtre pour les lignes afin de garder les lignes qui ont au moins deux arrêts en Suisse.

[^8]: Disponible à l'adresse: \url{geofabrik.de/geofabrik/geofabrik.html}

\pagebreak

### Problèmes rencontrés sur le set de données

Au fur et à mesure de l'avancement sur l'affinage du set de données initial, nous avons donc vu que certaines données comme le fichier `shapes.txt` étaient manquantes. Nous avons remarqué que le fichier `stops.txt` était incomplet et avons eu besoin de coupler les données avec les (+SITG_a) pour gagner en précision.

Nous nous sommes rendu compte que le set devait donc être modifié pour suivre une séquence logique dans la succession des bons arrêts et avons remarqué qu'il n'était pas possible d'importer les données relatives à la zone française, ce qui nous a obligé à filtrer les données suisses tout en ne gardant que les deux trajets (aller et retour) les plus récurrents pour chaque ligne.

En-dehors des problèmes liés au travail en lui-même, le set de données nous a forcé à faire quelques modifications pour pouvoir importer les données dans A/B Street. C'est notamment le cas des trajets qui bouclent comme le bus 52. La logique de A/B Street ne tient pas compte des trajets qui bouclent et cause une erreur spéciale :

```md
Person 272031 fell asleep on Bus #152291 and just rode off-map
```

Ce n'est pas un point réglable facilement et nous n'avons pas jugé nécessaire d'importer la ligne 52 qui représente une infime partie du réseau des (+TPG_a). Nous avons également décidé de ne pas importer les noctambus qui ne sont pas pris en compte dans le scénario de Ilias N'hairi [@nhairi_project] modélisant les déplacements des gens dans le canton de Genève. Ceci s'éxplique par le fait que les gens se déplacent entre 6 h 00 et 00 h 00 et ne sont donc jamais dans ces bus qui passent la nuit.

En outre, nous avons aussi remarqué qu'il manque des arrêts. Par exemple, dans le fichier `stoptimes.txt` qui décrit l'ordre de succession des arrêts, il y a des arrêts qui n'existent pas dans le fichier `stops.txt`. Après quelques recherches, on se rend compte que, soit l'arrêt a été supprimé en 2022, mais est toujours présent dans le set de données (+GTFS_a), soit l'arrêt a été "oublié" (ce qui est le cas la plupart du temps). Cela implique de devoir ajouter ces quelques informations à la main (environ 10 arrêts sur 1900).

De cette manière, et malheureusement, tout le travail que nous faisons ne peut pas être totalement reproduit avec un set de données vierge. On pourrait cependant partir du principe que nous avons fait un travail conséquent et fastidieux puis transmettre ces données aux (+TPG_a) afin qu'elles soient réutilisées les années suivantes à la place de l'ancien set (+GTFS_a) pas assez précis pour réaliser des simulations.

\pagebreak

## L'import des données dans A/B Street

### La particularité de l'import actuel

Il est important de rappeler que l'import des bus, qui a été réalisé par Dustin Carlino pour la ville de Seattle, a été ajouté hâtivement pour ce projet de bachelor. On pourrait donc dire que ce module d'import de données (+GTFS_a) est une ébauche permettant de modéliser les déplacements des gens en bus.

Toutes les fonctionnalités apportées par les (+GTFS_a) ne sont donc pas disponibles pour l'instant. C'est, par exemple, le cas des horaires auxquels passent les bus. Ceci a une forte influence sur la simulation actuelle, car il est alors impossible d'identifier le trajet à prendre en fonction de la journée. En d'autres termes, chaque ligne ne peut suivre, actuellement, qu'une route dans la simulation.

En conséquence, parmi tous les fichiers présents dans la nouvelle structure, seulement les fichiers `routes.txt`, `trips.txt`, `shapes.txt`, `stops.txt` et `stop_times.txt` sont conservés.

### Le fonctionnement de l'import

L'import des données dans A/B Street pourrait être considéré en lui-même comme une application à part entière. Lorsque l'on parle d'import, on parle d'ajouter une ville sur laquelle faire une simulation. Il faut donc importer la carte (+OSM_a), importer les transports en commun, importer un scénario...

Si nous nous concentrons sur la partie "import des (+TPG_a)", dans l'application, c'est un module dans lequel on doit non seulement importer les données, mais également vérifier la cohérence des données, trouver le plus court chemin entre 2 arrêts pour déterminer le trajet exact à réaliser, vérifier que les arrêts d'une ligne se succèdent dans un ordre logique, vérifier que le trajet ne boucle pas sur lui-même, que les arrêts sont placés aux bons endroits...

\pagebreak

Cependant, le set de données modifié comporte beaucoup de problèmes. En effet, la structure des (+GTFS_a) permet d'être très voir trop flexible sur la manière de stocker les données. Par exemple, il existe un champ dans le fichier `routes.txt` intitulé `route_type` qui permet d'identifier si la route correspond à une ligne de tramways ou de bus. La documentation officielle des (+GTFS_a) [@doc_google_gtfs] ne spécifie pas quelle donnée mettre en fonction du type de route. Sur notre set de données, le champ `route_type` vaut 300 si c'est une ligne de bus et 900 si c'est une ligne de tramway contre respectivement 1 et 2 dans le set de données (+GTFS_a) de Seattle. L'import a été réalisé en fonction des paramètres renseignés dans le set de données (+GTFS_a) de Seattle et il a donc fallu adapter toutes les données des (+TPG_a) ce qui a pris beaucoup de temps.

En outre, nous avions évoqué le fait que les horaires ne sont, pour l'instant, pas encore implémentés lors de l'import. Il est donc impossible d'avoir plusieurs trajets différents pour une ligne. Il a donc fallu adapter les données afin que chaque ligne ait une variante A ou B permettant d'indiquer le sens aller et le sens retour.

Voici le résultat de notre set de données :

\cimg{figs/resultat_gtfs}{scale=0.7}{Représentation du set GTFS}{Source : \url{bl.ocks.org/kaezarrex}, ref. URL05}

Sur la figure 2.7, on observe que le réseau des (+TPG_a) représenté par la structure (+GTFS_a) semble être cohérent. Les lignes se dirigent vers le centre de la ville qui est mieux desservi et pour la ligne F que je connais (en jaune), son trajet semble être bon. Une fois les modifications apportées et l'import complète, nous pouvons tester notre modélisation dans A/B Street.

## Premier test après import

Le set de données initial a bien changé depuis que nous l'avons récupéré sur la plateforme des données publiques pour la mobilité en Suisse [@le_site_des_gtfs]. Nous y avons apporté beaucoup de modifications et l'avons testé une première fois dans A/B Street. Les (+SITG_a) nous ont été d'une grande aide pour améliorer le set de données (+GTFS_a) et on observe déjà un premier résultat satisfaisant :

\cimg{figs/resultat_abs_network.png}{scale=0.35}{Représentation du set GTFS}{Source : \url{abstreet.org}, ref. URL01}

Avec la figure 2.8, on remarque que le réseau des (+TPG_a), une fois importé dans A/B Street, possède une tendance relativement bonne.

\pagebreak

\cimg{figs/resultat_sitg_network.png}{scale=0.5}{Représentation du réseau réel des TPG}{Source : \url{sitg.ch/app}, ref. URL11}

Sur cette figure, on constate effectivement plusieurs ressemblances avec la figure 2.8 qui nous montrent que nous gagnons petit à petit en précision. Si cela ne suffit pas pour tirer des conclusions, c'est tout de même intéressant de voir que la plupart des données sont importées avec succès.

### Les erreurs d'import

Si la plupart des données sont importées avec succès, il existe tout de même certains problèmes. Un premier exemple touche les lignes qui sont en bordure de la carte. Dans A/B Street, un bus qui devrait continuer en dehors de la carte (comme une ligne frontalière) quitte la carte à travers une bordure. Lorsque le trajet et le chemin à prendre est calculé par A/B Street, il se peut qu'il ne trouve pas de bordure ou alors qu'il essaye du le placer à un endroit auquel le bus n'a pas accès.

La solution à ce problème est arrivée un peu par hasard en agrandissant la carte afin d'englober toutes les lignes dans le polygone. Pour les lignes frontalières, il a fallu modifier légèrement le code de A/B Street afin d'être plus permissif sur les bordures lorsque les lignes sont coupées et dépassent du polygone.

\pagebreak

De la même manière, à l'import, A/B Street trouve le plus cours chemin à prendre et les lignes qui bouclent posent souvent des problèmes. Cette fois-ci, la solution la plus simple est de supprimer complètement toutes les lignes qui bouclent (36,42,55,72,A1,A2,A3,A4,A5,A6). Ce ne sont de toute façon pas des lignes importantes donc nous pouvons nous permettre de les omettre dans notre simulation.

Par ailleurs, il n'y a pas eu vraiment de problèmes pour le choix des arrêts en fonction des trajets. Le code réalisé dans l'analyseur de données nous a permis de vite passer à l'étape suivante sans avoir trop de trajets où les arrêts sont, en fait, ceux du sens inverse par exemple.

Cependant, pour rester sur l'import des arrêts, il s'avère que certains ne sont pas importés à cause de la distance qui les sépare des trottoirs. En effet, les coordonnées GPS ne sont pas toujours exactes et parfois, les arrêts se trouvent trop loin d'un trottoir. Si augmenter la distance limite de 3 à 5 mètres semble à première vue être une bonne idée, ce n'est pas du tout le cas puisque cela impacte grandement les déplacements des gens.

En effet, si l'arrêt se trouve trop loin de la route, mais qu'il est quand même importé, le bus s'arrêtera pour y déposer des passagers qui se retrouveront sur la route, ce qui est complètement interdit dans A/B Street à moins que ce soit un passage piéton. Pour les quelques arrêts dont c'est le cas (environ une dizaine), il semblait plus intéressant de modifier les coordonnées à la main pour être plus proche de la réalité et ainsi, importer les arrêts manquants.

En revanche, un souci beaucoup plus préoccupant est celui des lignes de tramways. Ces dernières ne sont pas importées telles quelles dans A/B Street, mais plutôt comme des lignes de bus.

En effet, dans A/B Street, la notion de tramway n'existe pas. Les transports en commun sont uniquement des bus. Dans la majeure partie des cas, les bus (qui sont en fait des tramways) suivent leurs lignes de bus, mais parfois, il se peut que le chemin le plus court soit de passer par la voie des voitures ce qui rend le tracé moins précis.

C'est d'autant plus problématique que les arrêts de tramways ne se font pas sur des trottoirs, mais sur des plateformes de transit. Au début, cela avait pour effet de n'importer presque aucun arrêt pour les tramways. La solution a été une nouvelle fois de modifier le code de A/B Street afin d'ajouter des trottoirs de chaque coté des voies de bus (qui sont en fait des lignes de tramway) pour pouvoir tout de même importer les arrêts.

D'autre part, il existe aussi plusieurs problèmes qui sont causés par la précision de (+OSM_a) et de l'import de la carte.

\pagebreak

### Les problèmes liés à Open Street Map

Nous avions évoqué le fait que la carte est importée avec (+OSM_a). Si cet outil collaboratif permet de faire des cartes précises, il n'en reste pas moins que parfois, la topologie de la ville est tout simplement un enfer à représenter. Voici un exemple d'un croisement de routes dans le quartier de Plainpalais à Genève :

\cimg{figs/plainpalais_abstreet.png}{scale=0.25}{Topologie d'un croisement au sud de Plainpalais sur A/B Street}{Source : image tirée de A/B Street disponible sur \url{abstreet.org}, ref. URL01}

On remarque que c'est une portion de la carte vraiment compliquée à modéliser au vu du nombre de routes qui se croisent et du trafic assez important qui s'y passe chaque jour. Voici le même croisement tiré du site d'Open Street Map :

\cimg{figs/plainpalais_osm.png}{scale=0.25}{Topologie d'un croisement au sud de Plainpalais sur Open Street Map}{Source : \url{openstreetmap.org}, ref. URL01}

\pagebreak

À partir des figures 2.10 et 2.11, on observe donc que la modélisation n'est pas parfaite sur A/B Street. Cependant, nous avons remarqué que ces problèmes se situent en très grande majorité dans le centre de Genève. En effet, la circulation y est plus complexe qu'en périphérie et il y a nécessairement moins de problèmes liés à la complexité naturelle des routes.

\cimg{figs/ligne_18_sitg.png}{scale=0.4}{Tracé de la ligne 18 tiré des SITG}{Source : \url{sitg.ch/app}, ref. URL11}

Sur cette première figure, on observe le tracé de la ligne 18 tel qu'il est réellement.

\cimg{figs/ligne_18_abs.png}{scale=0.4}{Tracé de la ligne 18 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

Maintenant, avec cette seconde image, on remarque que le tracé de cette même ligne dans A/B Street est bien différent, mais uniquement dans le centre-ville, là où le trafic y est plus complexe naturellement.

Il existe également d'autres erreurs qui viennent, elles, directement des ajouts faits par les différents utilisateurs. Prenons l'exemple de la ligne 19 pour illustrer un problème qui apparaît à une multitude d'endroits sur la carte :

\cimg{figs/ligne_19_arret_abstreet.png}{scale=0.3}{Topologie du trajet emprunté par la ligne 19 sur A/B Street}{Source : image tirée de A/B Street disponible sur \url{abstreet.org}, ref. URL01}

Voici maintenant la topologie réelle du trajet :

\cimg{figs/ligne_19_arret_reel.png}{scale=0.3}{Topologie réelle du trajet emprunté par la ligne 19}{Source : \url{tpg.ch}, ref. URL07}

\pagebreak

On remarque que, dans A/B Street, le trajet a une forme étrange entre les deux arrêts. La raison de ce problème est liée au fait que, dans la carte importée avec (+OSM_a), la route est à sens unique entre les deux arrêts. Au moment d'appliquer l'algorithme du plus court chemin, il devient alors impossible de prendre la route attendue et l'algorithme trouve une autre route qui fait un détour.

Ceci ouvre aussi sur un problème lié à la recherche du plus court chemin qui ne trouve parfois, aucun chemin pour importer la ligne. Nous revenons donc indirectement au problème de la complexité naturelle qui désigne tous les croisements et les axes de transports qui sont difficilement représentables dans (+OSM_a) parce qu'ils sont réellement complexes. De ce fait, lorsque la représentation est defétueuse, il arrive qu'un chemin ne soit pas trouvable ou qu'un chemin soit trouvé mais ne soit pas le bon (comme celui de la ligne 18). C'est la raison pour laquelle il est alors indispensable de modifier les données de (+OSM_a) pour avoir une meilleure précision dans le trajet des bus.

## Modifications dans Open Street Map

Nous avons vu que (+OSM_a) est la base sur laquelle la carte du simulateur est construite. Après l'import des données sur les (+TPG_a), nous avons remarqué que certains arrêts ne sont pas importés et que plusieurs lignes ne possèdent pas le bon trajet ou ne sont même pas importées. Il s'avère que certains de ces problèmes peuvent être réglés dans la mesure où (+OSM_a) est un outil de cartographie collaboratif et qu'il est donc possible d'y apporter des modifications afin de régler ces problèmes.

### Importer les lignes et arrêts

Le premier problème qui touche les arrêts est un problème assez atypique puisqu'il apparaît presque uniquement dans la ville de Genève. (+OSM_a) est un outil très complet qui permet de faire beaucoup de chose, mais qui laisse donc aussi beaucoup de place au libre choix des utilisateurs. Il est possible de représenter n'importe quel type de route comme des pistes cyclables, des voies de bus ou encore des doubles-voies mais il est étrangement possible de materialiser les trottoirs comme des routes seules. C'est exactement ce que fait Genève (sans doute par convention entre les utilisateurs) et c'est une très mauvaise pratique dans la mesure où un trottoir devrait nécessairement être lié à une autre route (d'où le terme employé dans OSM de `sidewalk` : un espace pour marcher sur le coté de la route).

\pagebreak

Par exemple, pour la ville de Seattle, lorsqu'une route est répertoriée dans (+OSM_a) on lui ajoute directement dans ses attributs des informations sur les trottoirs de chaque côté de la route. À Genève, en revanche, les trottoirs sont complètement séparés des routes qui ont un attribut `no-sidewalks`. Ils sont donc référencés dans (+OSM_a) mais pas reliés aux routes.

C'est un problème très préoccupant, car il devient assez compliqué de savoir quand et où mettre des trottoirs. En effet, le module permettant d'extraire les données de (+OSM_a) ne prend pas en compte les trottoirs qui sont séparés de la route. Il a donc fallu modifier le code de A/B Street afin d'ajouter manuellement des trottoirs lorsque c'est nécessaire.

En outre, il a aussi fallu modifier (+OSM_a) à certains endroits pour les routes où il manquait effectivement des trottoirs. Ceci dans le but d'importer la plupart des arrêts et d'avoir une simulation plus précise. Voici un exemple d'attribut qui a dû être ajouté à une route pour avoir les trottoirs et importer l'arrêt qui se trouve à proximité :

\cimg{figs/sidewlaks.png}{scale=0.4}{Information sur le Chemin de Pinchat depuis Open Street Map}{Source : \url{openstreetmap.org}, ref. URL10}

Avec la figure 2.16, on remarque qu'ajouter des attributs aux routes est une chose assez simple à condition de bien comprendre ce que l'on fait et d'avoir lu la documentation officielle avant.

### Lissage des trajets

D'autre part, (+OSM_a) n'impacte pas seulement les arrêts et les trottoirs, mais également le tracé des lignes. Comme évoqué précédemment, certaines lignes ne sont pas importées ou ne suivent pas le bon tracé du fait que certaines données dans (+OSM_a) sont erronées. Voyons deux exemples du tracé de la ligne 19 qui illustrent ces soucis récurent dans le simulateur :

\cimg{figs/jonction_abs.png}{scale=0.2}{Tracé de la ligne 19 à la Jonction tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\pagebreak

Dans un premier temps, nous nous intéressons à la partie en jaune qui se situe après l'arrêt `Sainte-Clothilde`. Sur cette figure et cette partie de l'image, on remarque un problème récurent dans (+OSM_a) pour la ville de Genève.

Pour mieux comprendre le problème, voyons le tracé réel de la ligne 19 à cet emplacement :

\cimg{figs/ligne_19_jonction_sitg.png}{scale=0.4}{Tracé de la ligne 19 à la Jonction tiré des SITG}{Source : \url{sitg.ch/app}, ref. URL11}

\pagebreak

Avec la figure précédente, on remarque que le trajet n'est pas le même. Toujours en restant sur le problème situé après l'arrêt `Sainte-Clothilde` (le `Boulevard Carl-Vogt`) il apparaît que le problème dans le tracé est lié aux données dans (+OSM_a) :

\cimg{figs/boulevard_carl_vogt.png}{scale=0.2}{Informations sur le `Boulevard Carl-Vogt` tirées de OSM}{Source : \url{openstreetmap.org}, ref. URL10}

Ce que l'on remarque ici, c'est que la rue est en sens unique. Il y a cependant une exception avec les bus qui peuvent rouler dans les deux sens. Ces spécificités ne sont souvent pas intégrées dans (+OSM_a) mais sont pourtant vraiment essentielles pour que les bus puissent suivre un chemin cohérent avec la réalité.

Il a donc été nécessaire de faire des modifications de ce genre pour beaucoup de routes dans le centre-ville de Genève afin d'obtenir le résultat souhaité :

\cimg{figs/boulevard_carl_vogt_abs.png}{scale=0.2}{`Boulevard Carl-Vogt` tirées de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\pagebreak

Le souci avec cette méthode, c'est qu'il n'existe aucune manière de trouver par avance où il y a des erreurs. Le seul moyen de trouver où faire les modifications, c'est de regarder au cas par cas la forme des trajets qui sont importés dans A/B Street. Cependant, on peut déjà observer que le tracé de la ligne 19 a changé pour laisser place au second problème :

\cimg{figs/jonction_abs_zoom.png}{scale=0.3}{Second soucis avec la ligne 19 dans A/B Street}{Source : \url{abstreet.org}, ref. URL01}

En réalité, ce problème très fréquent est lié au fait que l'intersection empêche tous les véhicules de tourner à droite (sur la route blanche) en direction de l'arrêt suivant. Cette information est fausse puisque les bus des (+TPG_a) ont le droit de tourner à droite. Il faut donc modifier les attributs de l'intersection dans (+OSM_a) afin de modifier le tracé du bus 19 à cet emplacement précis :

\cimg{figs/jonction_osm.png}{scale=0.2}{Intersection à la Jonction tirée de OSM}{Source : \url{openstreetmap.org}, ref. URL10}

\pagebreak

Avec la figure 2.22, on remarque qu'il est possible d'interdire l'accès aux véhicules et de faire une exception pour les bus. Ceci fait, on peut donc observer le résultat de nos modifications en comparant cette partie de la ligne 19 avec le tracé des (+SITG_a) illustré sur la figure 2.18 :

\cimg{figs/jonction_final_abs.png}{scale=0.35}{Intersection à la Jonction tirée de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

Nous remarquons donc l'effet de nos modifications qui doivent aussi être faites sur l'ensemble des lignes afin d'apporter plus de précisions, non seulement dans A/B Street, mais également pour tous les outils qui utilisent (+OSM_a) avec la ville de Genève.

## Import avec un scénario plus précis

En parallèle de ce travail assez fastidieux sur le lissage des lignes dans A/B Street et (+OSM_a), il a aussi fallu intégrer le travail de Ilias N'hairi [^9] au projet actuel. Pour ce faire, il y a eu plusieurs correctifs intéressants à apporter dans A/B Street afin de faire fonctionner le scénario avec les bus. Sans rentrer dans les détails, il arrivait à certains bus d'apparaître sur une voiture ce qui faisait planter A/B Street. Une autre erreur, plus drôle, concernait les bus qui se retrouvaient bloqués dans le trafic devant un arrêt. Les personnes descendaient et remontaient dans le bus à l'infini et le bus ne quittait jamais son arrêt même si la circulation le permettait. Il y a eu toute une liste d'erreurs à régler avant de pouvoir combiner les deux travaux.

L'intérêt de ceci réside dans le fait que nous pouvons comparer la fréquentation des (+TPG_a) dans A/B Street avec les données réelles. De cette manière, il nous est possible de mesurer la qualité de nos deux projets. D'autres mesures peuvent être faites sur la qualité de l'import des données comme classer les lignes et les arrêts importés ainsi que comparer le tracé réel à celui des lignes dans le simulateur.

[^9]: Disponible à l'adresse: \url{https://gitedu.hesge.ch/ilias.nhairi/population_generator}

\pagebreak
