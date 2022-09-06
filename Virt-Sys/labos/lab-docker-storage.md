
## partie 1

pour créer une arboresence Busybox:

avec le mount, on remarque que les couches sont liées entre elles via l'overlay

si on crée un fichier dans le dossier merged, rien ne se passe dans lower par contre le comportement est le même dans upper

la couche reaed_write (couche container) -> correspond à la couche upper
la couche d'image est représentée par la couche lower
la couche d'overlay est représentée par la couche merged

lorsqu'un fichier est crée dans la couche merged, il est enfaiiiiite ajouté dans la couche upper
lorsqu'un fichier existant dans la couche lower est modifié dans la couche merged, il est modifié dans la couche upper

lorsqu'un fichier existant dans merged et dans lower est supprimé, il est ajouté dans upper

## partie 2

pour créer un container avec Fedora:26:		docker run --name="fedora" -it fedora:26 /bin/bash

on a 1 couche basse à /var/lib/docker/overlay2/f3ee1255521f4bb549ee3d43dc5fa4ac80f4c8bf1326bb00732c5b39c6795e98/diff

to be continued ?

## partie 3

la version de Debian la plus récentre trouvée sur le docker hub est la 11.3

docker diff: A -> a file or directory was added, D -> a file or directory was deleted, C -> a file or directoy was changed
avec docker commit, on a ajouté 1 couche qui fait 64 MB.

## partie 4

créer un serveur web avec docker:	docker run -d -p8011:80 --name websrv01 hepia/docker_ex04:latest
pour accèder au docker hub avec le server web:		curl http://localhost:8011
docker run -d permet de lancer le docker en "détaché" (= arrière plan)
-p 8011:80 permet de maper le port TCP 80 au part 8011 du container
-name permet de définir un nom pour le container

le fichier se trouvant dans /usr/share/nginx/html/ex04 est accessible avec:	curl http://localhost:8011/ex04
pour afficher le contenu du dossier, on doit faire:		docker exec -it <container-name> /bin/bash
une fois qu'on est dans le container on peut faire un ls et on voit qu'on a un fichier nommé file_ex04 dans le dossier ex04

docker logs websrv01 permet de lister toutes les connexions au serveur nginx sur le container websrv01

pour créer un volume:		TO BE CONTINUED
