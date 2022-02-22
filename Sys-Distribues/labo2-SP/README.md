# Synchronous Shortest Path
## Description du projet

Travail réalisé par Trung Nguyen et Gustavo Pertuzati dans le cadre du module "systèmes distribuées". Ce projet a pour but d'implémenter l'algorithme distribué du plus court chemin de manière synchrone, en python et en utilisant les sockets comme paradigme de communication. 

## Le projet
5 serveurs, considérés comme des noeuds, sont lancé simultanément avec comme paramètres le numéro du port de communication, son fichier de voisins, et la commande "WAIT". Un autre serveur est lancé avec les mêmes paramètres à l'exception du dernier qui sera cette fois-ci "INIT". Ainsi ce dernier nœud commence l'exécution sans attendre la réception du premier message.

## Prérequis 
Ce projet utilise
```
- Python3
- 6 Machines virtuelles AWS
```

## Récupérer le projet
Le projet est disponnible sur gitedu.hesge.ch, pour le récupérer localement il faut cloner le projet avec la commande suivante:
```
git clone https://gitedu.hesge.ch/hoanhduc.nguyen/shortest_path_sysdistr.git
```
**Attention! Pour pouvoir utiliser le programme, il faut que le repo soit cloné dans le répértoire "HOME" ou "~"!!**

## Lancer le projet
Pour executer le programme, il faut utiliser la commande:
```
python3 deploy.py
```
**Attention! Pour pouvoir utiliser le programme,le script a tous les ips entrés dans la ligne de commande et il crée les xterms avec la commande ssh**


## Contact

### Auteurs
* Trung Nguyen (hoanh-duc-trung.nguyen@etu.hesge.ch)
* Gustavo Pertuzati (gustavo.pertuzati@etu.hesge.ch)
-