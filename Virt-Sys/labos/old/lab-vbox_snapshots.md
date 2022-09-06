# Réponses TP2:
## ex1
- Quels formats d'images sont proposés sur le site osboxes.org, en particulier que contiennent ces différents formats d'images, et quelles sont leurs différences ?

les formats d'images proposée est .vdi, ils contiennent 

## ex2
- Si la VM de l'exercice 1 n'est pas déjà en cours d'exécution, démarrez-la. Essayez ensuite de la cloner. . . Est-ce possible ?

non, car la vm est de l'ex1 est en cours d'exécution, hyperviseur met un verrou sur le disque .vdi pour une Vm utilisée

- Quels fichiers sont créés par ce premier snapshot ? Où se trouvent-ils, quelles sont leurs tailles, et que contiennent ils ?

Les fichiers dans le dossier Snapshots qui se trouve dans le dossier de votre nom_vm. il y a deux fichiers: .vdi et .sav
.vdi est de taille 16.8 MB
.sav est de taille 130.3 MB
le .vdi contient une copie de la mémoire.

- Continuez à utiliser votre machine virtuelle, en y créant des fichiers, par exemple en copiant des répertoires ou avec dd et observez la taille des fichiers snapshots (pendant 5 minutes d'utilisation par exemple).

On remarque que la taille du fichier Vdi a augmenté, ce qui semble logique car c'est une copie de la mémoire de la vm, et comme on a crée des fichiers ou des répertoires, cela augmente la taille. 

- Où est-ce que la configuration système (nombre de CPU, RAM, etc.) de ce nouveau snapshot est-elle sauvegardée ? 

Dans le dossier "Snapshots" se trouvant le dossier de votre vm. 

snapshot: il prend en photo une vm, y compris la ram. 

- Restaurez alors les différents snapshots que vous avez effectués précédemment afin de vous familiariser avec le mécanisme de restauration. Quelle est la contrainte principale pour restaurer un snapshot ?
la contrainte principale est qu'il faut effacer le snapshot actuelle de la vm, et eteindre la vm actuelle

- Si on considère les snapshots comme des noeuds, par quelle structure de données pourrait-on représenter ces snapshots ? (pas forcément ceux que vous avez effectués, mais de manière générale)

on peut représenté ces snapshots par la structure de données: une arbre binaire

- Est-ce que restaurer un snapshot précédent possédant une configuration système différente (paramètres CPU, RAM, etc différents) rétabli la configuration système existante au moment
du snapshot ?

non

- Maintenant que vous avez utilisé les mécanismes de clone et snapshot, quelles sont les différences (aussi en terme de limitations) entre effectuer un clone d'une VM et un snapshot ?

Différence entre une snapshots et un clone:
clone: réplique une vm -> la configuration, son espace de stockage, les états des différentes devices de la vm, il copie le disque. on réplique lorsque la vm n'est pas allumée.
snapshots: on prend en photo l'état de notre vm à un moment T, toutfois, on ne réplique pas la configuration de notre vm, le disque

## ex3

- Au niveau des données stockées sur le disque de l'hyperviseur, quelle est la différence entre effectuer un snapshot d'une VM en cours d'exécution et une VM arrêtée ("éteinte") ?

prendre un snapshot sur une vm arrêté ne sauvegarde pas l'état de la mémoire contrairement à la vm qui marche

- Est-ce qu'il y a des conséquences à effectuer un grand nombre de snapshots pour une VM donnée ?

un grand nombre de snapshots peut saturer la mémoire car l'état de la mémoire contient beaucoup de données. 

## ex4

le hack: modifier le fichier /etc/passwd

