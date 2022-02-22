Ultra-cp, travail pratique de fin de semestre réalisé par Thomas DAGIER dans le cadre du cours de Programmation Système de M. Guillaume Chanel entre le 09/12/2020 et le 19/01/2021.
Insipré du programme rsync, ce projet est une application permettant de faire des backups d'architecture de fichiers.

Compilation du projet : 
     make 

Execution du programme :
    - Listing de fichiers:
        ./ultra-cp <src>
    - Backup de dossiers et fichiers:
        ./ultra-cp <params> <src> <dst>
        
        <params> -> -a, -f, -af
        <src> -> possibilité de mettre plusieurs sources différentes (fichiers, dossiers, fichiers et dossiers ...) à condition que <dst> soit un dossier
        <dst> -> un fichier si c'est une copie de fichier à fichier, sinon, un dossier