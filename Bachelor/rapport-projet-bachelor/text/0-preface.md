# Remerciements {-}

Je souhaite remercier tout particulièrement Ilias N'hairi pour m'avoir apporté son précieux soutien vis-à-vis du Docteur (+OPM_a) Dipl Sc. (UniGE) PhD (EPFL) durant tout le déroulement de mon travail de bachelor. Un grand merci également à Simon Cirilli pour sa chaleureuse compagnie tout au long de ce projet.

Merci, un peu quand même, au Docteur (+OPM_a) pour ses quelques encouragements : « Bravo les garçons ! » et ses nombreuses critiques (parfois infondées).

\pagebreak

\cimg{figs/enonce.png}{scale=0.8}{}{}

# Résumé {-}

Le réseau routier du canton de Genève est en constante évolution. L'expansion des (+TPG_a) ou encore l'augmentation du nombre de vélos impliquent de devoir améliorer les routes actuelles pour répondre aux besoins de demain. Il peut donc s'avérer primordial de comprendre comment et pourquoi les gens se déplacent pour aider à la planification urbaine. Cela pourrait aussi permettre de modéliser des phénomènes très différents tels que la propagation du covid-19 en analysant les schémas de transmission liés aux déplacements des Genevois. Une bonne manière de réaliser ce travail serait de modéliser ces déplacements en utilisant un simulateur développé en Rust par Dustin Carlino depuis 2018. A/B Street, est un jeu sérieux permettant d'imiter le trafic routier d'une ville. Jusqu'alors, dans ce simulateur et pour le canton de Genève, il est possible de modéliser les déplacements des gens en voiture, à vélo et à pied. Ceci du fait que ces trois types de déplacements peuvent être aisément reproduit d'une grande ville à une autre. Ce n'est cependant pas le cas des transports en communs qui doivent être modélisés séparément puisqu'ils dépendent des sociétés de transports. L'objectif de ce travail de Bachelor est donc de reproduire le comportement des (+TPG_a) dans A/B Street afin de décrire avec plus de précision, les déplacements des gens dans le canton de Genève. Tout en présentant A/B Street et les différents acteurs de ce projet, ce rapport évoque la structure de données qui décrit le réseau des (+TPG_a). Nous insisterons aussi sur les étapes nécessaires à l'import des données dans le simulateur puis mesurerons la qualité du travail effectué en comparant des données réelles transmises par les (+TPG_a) avec celles de nos modélisations.

\begin{figure}
  \vspace{.1cm}
  \begin{center}
    \includegraphics[width=3.72cm,height=2.4cm]{figs/front-logo.png}
  \end{center}
\end{figure}
\begin{tabular}{ p{3cm} p{1cm} p{1cm} p{6cm}  }
  \multicolumn{1}{l}{Candidat :}& & & \multicolumn{1}{l}{Professeur-e(s) responsable(s) :}\\
  \multicolumn{1}{l}{\textbf{Thomas Dagier}} & & & \multicolumn{1}{l}{\textbf{Dr Orestis Malaspinas}} \\
  \multicolumn{1}{l}{Filière d'études : ISC} & & & \multicolumn{1}{l}{Travail de bachelor soumis à une convention de stage en} \\
  \multicolumn{1}{l}{} & & & \multicolumn{1}{l}{entreprise : non} \\
  \multicolumn{1}{l}{} & & & \multicolumn{1}{l}{Travail soumis à un contrat de confidentialité : non} \\
\end{tabular}

\pagebreak
