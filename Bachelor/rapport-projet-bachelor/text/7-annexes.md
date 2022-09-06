# Annexes

## Installer et éxécuter le simulateur A/B Street

### Prérequis

Premièrement, il vous faut installer une version de Rust stable sur votre machine (au moins la version 1.58). le procédé pour l'installation est disponible sur la [`documentation officielle`](https://www.rust-lang.org/tools/install).

- Sur Windows, il faudra sans doute installer [`Visual Studio 2019`](https://visualstudio.microsoft.com/downloads/)
- Sur Linux vous pouvez utiliser la commande:
  
  `sudo apt-get install libasound2-dev libxcb-shape0-dev libxcb-xfixes0-dev libpango1.0-dev libgtk-3-dev`

Il vous faudra aussi installer [`Docker`](https://docs.docker.com/get-docker/) et [`GIT`](https://github.com/git-guides/install-git) sur votre machine en fonction de votre système d'éxploitation.

### Exécution de A/B Street sur une machine Linux

Télécharger le repos git de A/B Street avec la commande:

`git clone https://github.com/thomasdgr/abstreet`

Ensuite, en vous déplaçant dans le dossier téléchargé avec la commande `cd`,

- pour importer la ville de Genève:
  
  `./import.sh --raw --map --city=ch/geneva`

- pour importer le plus petit package nécéssaire à faire tourner la ville de Seattle:
  
  `cargo run --bin updater -- download --minimal`

\pagebreak

Une fois les données de votre choix téléchargées, vous pouvez démarrer le simulateur avec la commande:
  
  `cargo run --bin game --release -- --dev data/system/ch/geneva/maps/center.bin --infinite-parking --disable-turn-conflicts`

Pour plus d'informations sur les fonctionalités disponibles et sur A/B Street de manière générale:

- [la documentation utilisateur](https://a-b-street.github.io/docs/user/index.html)

- [la documentation développeur](https://a-b-street.github.io/docs/tech/dev/index.html)

## Projet sur l'analyseur de données GTFS

Pour toute utilisation du projet, se référer à la documentation du [repo git](https://githepia.hesge.ch/thomas.dagierjo/tut-tut-les-bus)

\pagebreak