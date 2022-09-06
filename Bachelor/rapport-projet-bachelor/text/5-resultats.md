# Résultats

## Mesure des données importées

Grâce au travail effectué au cours de ce projet, nous avons maintenant un set de données avec des informations plus pertinentes et une carte avec des données plus cohérentes de par nos modifications apportées dans (+OSM_a). Il est maintenant important de mesurer la qualité de l'import actuel. Dans un premier temps, le plus simple est de regarder quelles lignes ne sont pas importées et comprendre pourquoi puis faire de même avec les arrêts.

### Les lignes

Comme nous l'évoquions plus tôt, la plupart des lignes ont été importées avec succès. Voici deux exemples de lignes qui sont importées correctement et leurs trajets dans A/B Street :

\cimg{figs/ligne_9_abs.png}{scale=0.35}{Tracé de la ligne 09 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\pagebreak

\cimg{figs/ligne_5_abs.png}{scale=0.32}{Tracé de la ligne 05 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

Il existe néanmoins certaines lignes qui ne sont pas importées dans A/B Street. Voyons l'exemple de la ligne E+ :

\cimg{figs/ligne_E_pl_abs.png}{scale=0.32}{Tracé de la ligne E+ tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\pagebreak

Sur la figure 3.3, on observe le tracé de la ligne E+ direction `Gare Cornavin`. En sens inverse, la ligne E+ ne peut pas être importée. Ceci est dû à l'import de la carte qui ne reproduit pas correctement une intersection au Pont du Mont-Blanc :

\cimg{figs/ligne_E_pl_intersection.png}{scale=0.6}{Intersection qui pose problème sur la ligne E+}{Source : \url{abstreet.org}, ref. URL01}

La ligne E+ est censée arriver par la gauche de la figure 3.4 (la longue flèche verte) et passer par cette intersection qui n'est pas correctement importée dans A/B Srteet. On comprend aussi pourquoi la ligne peut êre importée en sens inverse puisqu'elle ne passe pas par cette intersection douteuse. Après plusieurs tentatives et sans modifier la circulation actuelle dans (+OSM_a), il semble vraiment compliqué de régler cette erreur du fait que nous ne comprenons pas du tout d'où elle provient. De nouveau, cette ligne n'étant pas essentielle pour la simulation, nous avons fait le choix de ne pas nous attarder sur ce problème.

D'autres lignes comme le bus N, M ou 66 ne sont, elles, pas importés puisqu'ils ne comportent pas suffisamment d'arrêts en Suisse. Nous avions, en effet, évoqué le fait que l'outil Géofabrik utilisé pour importer la carte ne permet pas d'importer à la fois des données françaises et suisses et que nous étions donc forcé d'importer uniquement les lignes qui sont sur le territoire suisse.

De la même manière, nous n'avons pas importé les noctambus qui ne servent à rien dans le scénario ainsi que les lignes de bus qui bouclent. Nous pouvons tout de même nous satisfaire du fait que sur les 96 lignes (soient 192 trajets à importer) il y a 176 trajets qui sont importés avec succès. Cela, d'autant plus que la totalité des lignes non-importées sont des lignes avec une influence mineure sur la simulation des déplacements des gens.

### Les arrêts

Concernant les arrêts, la tendance est clairement la même. Si nous n'importons volontairement pas les arrêts situés du côté français, il existe quelques arrêts (7 arrêts sur 1776 arrêts du côté suisse) qui ne sont pas importés pour diverses raisons. Cela aura alors pour effet de modifier quelque peu le trajet de certaines lignes du fait que le plus court chemin entre deux arrêts ne donne pas toujours le bon résultat s'il manque des arrêts.

Toujours sur des lignes qui ont très peu d'influence sur la simulation, voici tout de même trois exemples d'arrêts qui ne sont pas importés :

\cimg{figs/arret_palexpo.png}{scale=0.27}{Problème avec l'arrêt Palexpo-Halle 7 tiré de OSM}{Source : \url{openstreetmap.org}, ref. URL10}

Sur cette première image, on observe que l'arrêt `Palexpo-Halle 7` se situe sous un bâtiment. C'est un cas très spécifique qui ne peut pas être réglé à moins de modifier complètement la logique du simulateur avec l'affichage des bâtiments. En effet, il faudrait faire en sorte que les routes situées sous des bâtiments se comportent comme des tunnels, mais ce n'est pas facilement modifiable dans A/B Street pour l'instant.

Heureusement cet arrêt n'est utilisé que par le bus 66 (qui n'est pas importé) et le bus 54 (dont le trajet reste inchangé). Ce n'est donc pas un problème majeur pour notre simulation des déplacements.

\pagebreak

Voici un autre exemple, toujours à l'aéroport sur la ligne 23 :

\cimg{figs/arret_p47.png}{scale=0.27}{Problème avec l'arrêt Aéroport P47 tiré de OSM}{Source : \url{openstreetmap.org}, ref. URL10}

Sur la figure 3.6, on observe que l'arrêt en question est littéralement situé sur un parking. Le souci est à peu près le même qu'avec l'arrêt précédent, mais cette fois-ci, l'arrêt en question est le point de départ ou d'arrivé de la ligne 23. Le souci est à peu près le même qu'avec l'arrêt précédent, mais cette fois-ci, l'arrêt en question est le point de départ ou d'arrivé de la ligne 23.

Observons un dernier exemple dans la campagne sur le trajet du bus 56 :

\cimg{figs/arret_chemin_des_Clys.png}{scale=0.27}{Problème avec l'arrêt Chemin des Clys tiré de OSM}{Source : \url{openstreetmap.org}, ref. URL10}

Sur cette dernière figure, on observe un cas assez étrange d'un arrêt où il n'existe vraiment pas de trottoirs pour descendre. Les personnes descendent du bus dans l'herbe et cela empêche d'importer l'arrêt du fait qu'il est indispensable, pour importer un arrêt, qu'il y ait un trottoir à proximité.

Mis à part ces quelques erreurs, nous pouvons être très satisfaits des données importées dans A/B Street, que ce soit pour les lignes et les arrêts. Nous pouvons aussi être satisfaits que les arrêts qui ne sont pas importés n'influent pas sur les tracés des lignes qui auraient pu changer.

À travers cette partie, nous avons vu que certaines lignes et arrêts n'étaient pas importés. Nous allons maintenant voir si les données importées reflètent le comportement réel des (+TPG_a).

## Qualité de l'import des trajets

Pour vérifier que l'import des données est cohérent, le plus simple est de faire une comparaison des trajets réels avec ceux dans A/B Street. De plus, cela permet de valider deux facteurs en même temps. Le premier est lié au fait que les données importées depuis (+OSM_a) sont correctes puisque le bus passe sans faire de détour. Le second nous permet de supposer que les arrêts sont importés correctement. Par cela, nous entendons que le bon arrêt est choisi correctement parmi ceux du même nom possible et qu'il ne perturbe pas le tracé du bus (ce qui pourrait être le cas si un arrêt n'est pas importé puisque le plus court chemin est fait entre deux arrêts successifs et pourrait donner un résultat différent si un arrêt n'est pas importé).

### Des données issues des SITG

Pour comparer les trajets nous nous basons sur les données des (+SITG_a). Ces dernières sont très fidèles à la réalité et sont lisibles très facilement à la différence des informations publiques des (+TPG_a) dont voici un extrait :

\cimg{figs/okami_gg.png}{scale=0.3}{Extrait de la topologie des TPG}{Source : \url{tpg.ch}, ref. URL07}

\pagebreak

Cette figure illustre le quartier de la `Gare Cornavin` et montre toutes les lignes qui y passent. Voici un exemple de données qui peut être tiré des (+SITG_a) au même endroit :

\cimg{figs/ligne_15_sitg.png}{scale=0.3}{Tracé de la ligne 15 tirée des SITG}{Source : \url{sitg.ch}, ref. URL11}

On remarque que les informations des (+SITG_a) sont beaucoup plus aisément exploitables pour comparer les tracés des lignes puisqu'il nous est non seulement possible d'isoler une ligne, mais également de voir son tracé sur un plan satellite.

\pagebreak

### Comparaison entre le modèle et le réel

Premièrement voici plusieurs comparaisons rapides sur des lignes de bus :

\cimg{figs/ligne_19_abs.png}{scale=0.3}{Tracé de la ligne 19 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/ligne_19_sitg.png}{scale=0.3}{Tracé de la ligne 19 tiré des SITG}{Source : \url{sitg.ch/}, ref. URL11}

\pagebreak

On remarque que les trajets sont en tout point les mêmes pour cette ligne.

Ici aussi, on retrouve beaucoup de similarités entre les deux figures précédentes.

\cimg{figs/ligne_7_abs.png}{scale=0.3}{Tracé de la ligne 7 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/ligne_7_sitg.png}{scale=0.3}{Tracé de la ligne 7 tiré des SITG}{Source : \url{sitg.ch/}, ref. URL11}

Ici aussi, on retrouve beaucoup de similarités entre les deux figures précédentes illustrant les tracés de la ligne 7.

\cimg{figs/ligne_F_abs.png}{scale=0.3}{Tracé de la ligne F tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/ligne_F_sitg.png}{scale=0.3}{Tracé de la ligne F tiré des SITG}{Source : \url{sitg.ch/}, ref. URL11}

\pagebreak

Dans un cas un peu particulier du fait que la ligne F ne soit importée que partiellement (uniquement le côté suisse), on remarque également que l'import est cohérent avec la réalité.

Il existe en revanche quelques lignes dont les trajets sont moins précis comme la ligne 1 :

\cimg{figs/ligne_1_abs.png}{scale=0.4}{Tracé de la ligne 1 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\pagebreak

\cimg{figs/ligne_1_sitg.png}{scale=0.4}{Tracé de la ligne 1 tiré des SITG}{Source : \url{sitg.ch/}, ref. URL11}

On constate une petite erreur sur la figure 3.16 au niveau de la `Gare Cornavin`. Ceci est dû à un problème d'import où A/B Street ne parvient pas à reproduire correctement une intersection par laquelle le bus 1 est censé passer. En revanche, ce qui pourrait ressembler à une erreur si nous regardons la figure 3.17 n'en est en fait pas une puisque les (+SITG_a), pour cette ligne, représente les différents trajets qui ont pour terminus l'arrêt `Hôpital-Trois-Chênes`. Il faut donc imaginer que le bus ne passe que pas un des deux tracés en rouge sur la droite de l'image (en l'occurrence, celui du bas).

\pagebreak

Voici aussi un exemple qui démontre le fait que les lignes qui bouclent ne doivent pas être importées pour l'instant dans A/B Street :

\cimg{figs/ligne_36_abs.png}{scale=0.3}{Tracé de la ligne 36 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/ligne_36_sitg.png}{scale=0.5}{Tracé de la ligne 36 tiré des SITG}{Source : \url{sitg.ch/}, ref. URL11}

On observe que la circulation y est vraiment complexe et ce n'est ni la faute des données de (+OSM_a) ni du set de données (+GTFS_a). Le problème est lié à la recherche du plus court chemin qui ne se comporte pas correctement à cause de la ligne qui boucle. Nous pouvons donc dire qu'au vu du nombre de problèmes que nous posent les lignes qui bouclent, il semble judicieux de ne pas les importer pour l'instant d'autant plus qu'elles n'apportent pas grand-chose à la simulation.

Voyons maintenant le cas de la ligne de tramway 12 :

\cimg{figs/ligne_12_abs.png}{scale=0.4}{Tracé de la ligne 12 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/ligne_12_sitg.png}{scale=0.4}{Tracé de la ligne 12 tiré des SITG}{Source : \url{sitg.ch/}, ref. URL11}

\pagebreak

Malgré le fait que les tramways soient considérés comme des bus, on observe sur ces deux figures précédentes que le tracé de la ligne 12 direction `Lancy-Bachet-Gare` est quasiment parfait. Regardons maintenant le tracé de la ligne 12 dans l'autre sens (`Moillesulaz`) :

\cimg{figs/ligne_12_abs_inverse.png}{scale=0.4}{Tracé de la ligne 12 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/ligne_12_sitg_inverse.png}{scale=0.4}{Tracé de la ligne 12 tiré des SITG}{Source : \url{sitg.ch/}, ref. URL11}

\pagebreak

Avec ces deux figures, on remarque, cette fois-ci, que le tracé n'est plus du tout précis. C'est un problème qui intervient uniquement avec les lignes de tramways. En effet, ces dernières sont considérées comme des lignes de bus. Ceci implique des conséquences sur les routes comme à l'intersection suivante :

\cimg{figs/ligne_12_intersection.png}{scale=0.4}{Intersection posant problème sur la ligne 12 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

Sur la figure 3.24 on observe que la ligne de bus Sur la figure 3.24, on observe que la ligne de bus s'arrête subitement. Cela est dû à la mauvaise interprétation de A/B Street qui identifie une ligne de tramway comme une ligne de bus. De ce fait, le tramway (qui est en fait un bus) ne passe pas par cette route et doit donc faire un léger détours.

Outre les quelques problèmes avec ces lignes, nous pouvons dire que l'import est assez précis pour simuler correctement les déplacements des gens dans le canton de Genève.

\pagebreak

### Les limites de Open Street Map

Il existe néanmoins une autre ligne qui n'est pas très bien importée. Dans un sens, la ligne 5 possède un trajet qui dévie un tout petit peu du vrai tracé :

\cimg{figs/ligne_5_abs_intersection.png}{scale=0.3}{Intersection posant problème sur la ligne 5 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

Sur cette image, on suppose qu'un bus de la ligne 5 est situé sur la voie de bus en rouge. À partir de ce point, il est possible d'avancer tout droit (flèche bleue), de tourner à droite (flèche verte) ou de faire demi-tour (flèche violette). Il n'est cependant pas possible de tourner à gauche. En réalité, les voitures n'ont effectivement pas le droit de tourner à gauche alors que les bus peuvent. C'est un problème que nous avions déjà évoqué plus tôt et que nous sommes en mesure de régler.

Le souci, cette fois-ci, est qu'un utilisateur de (+OSM_a) bloque cette modification sans raison (alors que la modification apporte plus de précision). Nous avons eu beau retenter, il semblerait que la personne n'ait pas envie que les bus puissent tourner à gauche alors qu'ils devraient pouvoir.

Ce qui est intéressant ici, c'est que ce problème nous rappelle que (+OSM_a) est un outil collaboratif. Nous ne sommes donc pas à l'abri de voir certaines données modifiées comme celle-ci alors qu'elles sont cohérentes avec la réalité. De manière générale, dès qu'il y a une modification sur la ville de Genève, cela peut impacter en bien ou en mal la simulation et nous n'avons malheureusement aucun contrôle sur les données importées. Il faut juste espérer que les modifications soient faites pour améliorer (+OSM_a) et non pas pour un but précis comme c'est le cas pour l'usager qui bloque la ligne 5.

## Qualité de la modélisation des déplacements

À travers cette première validation, on peut donc dire que les trajets sont majoritairement très bien importés dans A/B Street. Afin de faire une double validation avec le travail de Ilias N'hairi[@nhairi], il pourrait alors être intéressant de comparer le nombre de personnes qui prennent un bus à une certaine heure dans A/B Street avec des données transmises par les (+TPG_a).

### Des données fournies par les TPG

Contactés au début du projet, les (+TPG_a) nous ont transmis des données sur la fréquentation des bus aux différentes heures de la journée pour les mois d'octobre et novembre 2021. Le travail à réaliser est donc de faire une moyenne des fréquentations d'une ligne à une certaine heure. On fait la moyenne sur toute la plage de données, soit un mois afin de connaître l'évolution du nombre de personnes qui sont dans les différents bus.

### Mesure des déplacements en tranports en commun dans A/B Street

Du côté de la simulation, on réalise un petit programme permettant d'extraire de A/B Street le nombre de personnes qui sont dans un bus donné à une heure arbitraire. Ici aussi, on fait une moyenne sur cinq exécutions afin d'éviter tout cas exceptionnel dans le scénario. Ensuite, on compare ces deux résultats sous la forme de graphiques qui décrivent, pour chaque arrêt du point de départ vers le terminus, le nombre de personnes actuellement dans le bus.

Premièrement, avant de regarder quels sont les résultats, on peut déjà supposer que la représentation du nombre de personnes dans le bus devrait à peu près ressembler à une gaussienne. En effet, il y a logiquement plus de personnes qui montent au début et plus de personnes qui descendent à la fin. Nous devrions donc nous attendre à avoir un pic de fréquentation aux arrêts importants comme `Bel-Air` ou aux arrêts qui se trouvent au milieu du trajet.

Il est aussi important de rappeler qu'au-delà de l'import des (+TPG_a) dans A/B Street et des résultats, cela permet surtout de valider le fait que notre simulation est cohérente avec la mobilité genevoise. Ceci dépend en très grande majorité du scénario généré puisque c'est lui qui orchestre les déplacements.

\pagebreak

Voici un premier exemple avec la ligne 6 :

\cimg{figs/6_abs.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 6 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/6_tpg.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 6 tiré des TPG}{Source : \url{tpg.ch}, ref. URL07}

Sur cette première comparaison, on observe, en rouge, les données tirées de A/B Street et en bleu, les données tirées des (+TPG_a). Nous pouvons remarquer que la tendance est plutôt similaire. De ce fait, nous pouvons affirmer que, pour la ligne 6 dans un sens et à une certaine heure, notre simulation reflète assez bien le comportement réel.

\pagebreak

Voyons maintenant comment s'organisent les déplacements dans un tramway avec la ligne 15 :

\cimg{figs/15_abs.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 15 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/15_tpg.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 15 tiré des TPG}{Source : \url{tpg.ch}, ref. URL07}

Ici aussi, on observe que les données sont plutôt similaires. Un autre point intéressant est que la charge moyenne du trafic est bien plus importante dans A/B Street pour un tramway que pour un bus. C'est assez encourageant puisque nous nous attendions à ce que les bus et les tramways aient autant de personnes à bord. Ceci nous permet donc de conclure que les lignes de tramways sont créées pour passer là où il y a beaucoup de demande et que la répartition en sous-secteurs statistique de la population est plutôt cohérente avec la réalité.

\pagebreak

Observons dès lors le cas de la ligne 19 :

\cimg{figs/19_abs.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 19 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/19_tpg.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 19 tiré des TPG}{Source : \url{tpg.ch}, ref. URL07}

Cette fois-ci, nous pouvons observer que les données sont beaucoup moins cohérentes avec la réalité. Même si la charge moyenne est du même ordre de grandeur, on observe bien que la courbe ne suit pas tout à fait la même tendance.

On peut tout de même noter que la forme est celle d'une gaussienne. Sans avoir de réelles suppositions, nous pouvons supposer que ces variations, qui interviennent lorsque les gens rentrent du travail, sont peut-être liés aux emplacements qui sont choisi pour y envoyer les gens la journée. En effet, les gens se déplacent à un certain endroit pour travailler et nous pouvons alors questionner le choix de ces emplacements de travail.

Enfin, voici une dernière comparaison pour la ligne 22 :

\cimg{figs/22_abs.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 22 tiré de A/B Street}{Source : \url{abstreet.org}, ref. URL01}

\cimg{figs/22_tpg.png}{scale=0.4}{Graphique de la charge moyenne de la ligne 22 tiré des TPG}{Source : \url{tpg.ch}, ref. URL07}

Sur ces deux dernières figures, nous pouvons observer que les courbes ne sont pas non plus tout à fait similaires. Cependant, pour ce cas de figure, ce qui varie grandement, c'est la charge moyenne qui n'est pas vraiment la même. Pour cet exemple, nous n'avons pas réellement d'explications si ce n'est que les gens prennent beaucoup le bus à cet endroit-là. Le problème est donc principalement lié au scénario.

Une autre explication serait que le scénario utilisé simule les déplacements de 10 % des gens dans le canton de Genève. Nous avons donc naïvement multiplié nos résultats par 10 pour avoir la charge totale sur la même échelle que celle fournie par les (+TPG_a). Il est donc très probable que nous perdions en précision à cause de cela.

Avec ces quelques exemples, nous constatons tout de même que la simulation présente des résultats très satisfaisant qui pourraient être améliorés par la suite.

## Perspectives d'améliorations

Pour gagner en précision dans la simulation des déplacements des gens dans le canton de Genève, il existe différents axes qui peuvent faire l'objet de futurs travaux. Premièrement, on pourrait imaginer un outil permettant d'importer à la fois des données de France et de Suisse. Ainsi, il serait possible d'ajouter plusieurs lignes comme le bus N ou le 66 qui ne sont actuellement pas importés. Nous pourrions aussi suggérer d'intégrer à A/B Street un autre moyen de déplacement afin que les tramways puissent avoir leurs propres lignes et ne soient plus considérés comme des bus.

Une autre idée, cette fois-ci, plus complexe à mettre en place serait de faire un outil d'import séparé, uniquement pour Genève afin d'importer correctement les trottoirs et les transit-plateforme ou tout autre données qui sont spécifiques au canton de Genève comme les lignes de bus qui bouclent ou les noctambus qui pourraient être intégré à un nouveau scénario.

Il ne semble plus y avoir de modifications à faire sur le set de données (+GTFS_a) qui semble bien aboutit maintenant. Cependant, il serait judicieux de continuer à apporter des modifications dans (+OSM_a) afin d'avoir une carte plus précise et de faire une simulation plus cohérente avec la mobilité genevoise.

\pagebreak
