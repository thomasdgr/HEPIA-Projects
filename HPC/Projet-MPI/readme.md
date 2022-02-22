## Projet de Calcul Hautes Performances

Réalisé par Thomas Dagier entre le 15 et le 29 Novembre 2021

### Compilation et exécution du projet

- requiert la libraire MPI. 
- à la racine du projet:

    - `make`

    - `mpirun laplace.out m n t`,  avec m, le nombre de colonnes de la matrice, n le nombre de lignes et t le nombre d'itérations à faire

    - `mpirun laplace.out borders.txt t`,  où le fichier correspond aux bords qui décrivent la matrice à créer et t le nombre d'itérations à faire

A la fin de l'exécution, le résultat est écrit dans le fichier `laplace.txt`