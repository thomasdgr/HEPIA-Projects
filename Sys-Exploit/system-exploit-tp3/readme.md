Compilation du projet :

make

Préparation et ajout du module :

insmod

# TP sur les modules

Projet réalisé Thomas Dagier dans le cadre du cours de Système d'éxploitation de M. Guillaume Chanel.

## Description du projet

Création de module de périphérique virtuel à partir d'un buffer statique circulaire

Cours : http://cui.unige.ch/~chanel/prez/presentations/sys-exploitation/

L'ennoncé du tp (abcd.pdf) contient des questions sur la partie "buffer statique". Les réponses sont dans le fichier questions.md

## Compilation du projet
```
make
```

## Préparation et ajout du module
```
insmod my-module.ko
cat /proc/devices | grep abcd (retourne le numéro majeur)
mknod /dev/abcd c (le numéro majeur) 0
```

## Execution du projet
```
./main
```