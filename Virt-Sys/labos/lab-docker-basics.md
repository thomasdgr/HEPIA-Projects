#lab-docker

## partie 0

### sur le server (la vm)

installer docker:	sudo apt-get install docker.io
placer l'utilisateur dans le group docker (ne jamais faire sudo avec docker): sudo usermod -a -G docker student (il faut sans doute relancer la connexion ssh pour que ça soit pris en compte)
lancer le service docker: sudo systemctl start docker.service
toujours le lancer au démarrage de la machine: sudo systemctl enable docker.service

## sur le client (le pc)

ouvrir une connexion ssh pour docker avec la machine: export DOCKER_HOST=ssh://student@10.136.27.8 (effectif que dans le terminal actuel)
vérifier que la connexion est active: docker info (devrait retourner des infos sur la vm)

## partie 1

sur la vm, on peut chercher les images docker avec: docker search hepia
pour lancer un docker sans le shell mais faire un ls à la racine: docker run hepia/docker_ex01 ls
on peut voir les containers qui sont utilisés actuellement: docker ps (comme on run sans le shell, on en a aucun d'actif)
on peut voir tous les containers qui ont été utilisés: docker ps -a (on en utilise un pour le run et il se stop dès que le run est terminé, on peut spécifier -rm au moment du run pour qu'il se supprime de lui même dès que le run est terminé)
- les noms des containers sont aléatoires, les IDs aussi, ils se quittent avec un status qui dépend du status de la commande éxécuté dans le run
- les images sont stockées sur le registry public "Docker Hub"

## partie 2:

docker run --rm hepia/docker_ex02 ls -l /ex02
en plus de terminer le container, le --rm va le supprimer de la liste des containers
dans le dossier /ex02, on a le fichier file_ex02

### partie 3:

quand on écrit un fichier sur un container, on écrit dans la partie mutable de l'image donc quand on restart le container avec l'image, on a toujours le fichier.
par contre, si on instantie un nouveau container à partir de l'image, on se base uniquement sur la partie non-mutable de l'image donc le fichier ne sera plus là.

SI ON EST ROOT QUAND ON LANCE LE CONTAINER, ON EST AUSSI ROOT DANS LE CONTAINER

ctrl+p et ctrl+q ont pour effet de nous détacher du container. pour nous rattacher, on doit faire un docker attach solution_ex03

on a que 1 container puisqu'on se rattache au container précédent.

le fichier existe toujours car on écrit sur la partie mutable du container.
pour que le container soit stoppé on peut faire un docker stop ou un docker rm.

to be continued ? 

## partie 4:

lancer un docker avec Alpine 3.15 et vérifier que la version est la bonne:		docker run alpine:3.15 cat /etc/alpine-release
le processus appartenant au root dans le container appartient aussi au root sur la machine host
 - pour le voir on peut faire un sleep dans le container et executer la commande ps

si un processus UID 0 dans le container est aussi UID 0 sur le host, on risque d'accèder à la machine host depuis le container en root

lorsqu'on fait un ps sur la machine host et dans le container, les PID sont différents.
ils sont différents car ils ne tournent pas dans le même contexte / namespace et n'ont pas accès aux informatitions des autres contextes.

execution du programme htop sur le container: pid = 2
execution du programme htop sur le host: pid = 155987

processus portant le numéro de PID 1 sur le host: sbin/init/mybe-ubiquity
processus portant le numéro de PID 1 sur le container: /bin/sh
Ils sont différents car ils correspondent au premier processus lancé sur les machines. C'est la raison pour laquelle c'est souvent /bin/sh qui possède le PID 1 sur un container

uname -rv sur le container: 5.4.0-97-generic #110-Ubuntu SMP Thu Jan 13 18:22:13 UTC 2022
uname -rv sur le host: 5.4.0-97-generic #110-Ubuntu SMP Thu Jan 13 18:22:13 UTC 2022
-> c'est la même chose

le contenu de /dev sur le container: 15 devices
le contenu de /dev sur le host: 200 devices
-> tous les devices ne sont pas mappés sur le container mais on peut le faire manuellement pour chacun d'entre eux 

C'est possible de donner à un container l'accès à un ou plusieurs périphériques de la machine host
-> exemple pour le device kvm:  docker run --name="alpine" --device /dev/kvm -it alpine:3.15

Execution de la commande mount:
le système de fichier racine sur le host: c'est celui de ubuntu
le système de fichier racine sur le container: c'est celui de la couche overlay
le rootfs du container est aussi sur le host dans /var/lib/docker/overlay2 -> on peut donc en conclure que le rootfs du container est géré par la machine host

les containers sont arrêtés mais existent encore. On peut utiliser l'argument --rm pour les supprimer complètement ou on peut les restart même s'ils n'apparaissent pas avec la commande docker container ls

