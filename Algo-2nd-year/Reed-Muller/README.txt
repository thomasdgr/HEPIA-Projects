Projet d'algorithmes avancées sur le code de correction d'erreur de Reed-Muller réalisé Thomas Dagier et Dorian Bernasconi


Objectif du projet:

    Implémenter le code de correction d'erreur afin de retrouver l'image d'origine, prise depuis Mars, qui est codée et bruitée.


Exécution du projet:

    javac Main.java
    java Main


Exemple d'utilisation du programme:

    Pour retrouver les images prisent sur Mars:
    - valeur de r = 5
    - seuil de bruit = 0.3
    - opération choisie = 2 (traiter une image)
    - fichier à charger = mars-crat.enc.alt_0.07 (ou mars-crat.enc.alt_0.10)
    - opération choisie = 5 (débruiter + décoder)
    - fichier où sauver = resultat.pgm
    - opération choisie = 0 (quitter le programme)
    -> puis regarder le résulat avec n'importe quel visionneur d'image

    Pour retrouver le mot (décimal) d'origine après avoir appliqué toutes les transformations:
    - valeur de r = 7
    - seuil de bruit = 0.3
    - opération choisie = 1 (traiter un mot)
    - mot à entrer = 20
    - opération choisie = 1 (encoder)
    - opération choisie = 3 (bruiter)
    - opération choisie = 4 (débruiter)
    - opération choisie = 2 (décoder)
    -> observer que les résultats se recoupent
    - opération choisie = 0 (quitter le programme)

    Pour retrouver l'image (pgm) d'origine après avoir appliqué toutes les transformations:
    - valeur de r = 7
    - seuil de bruit = 0.3
    - opération choisie = 2 (traiter une image)
    - fichier à charger = lena_128x128_64.pgm
    - opération choisie = 1 (encoder)
    - fichier où sauver = lena_encoded.pgm
    - opération choisie = 3 (bruiter)
    - fichier où sauver = lena_encoded_noised.pgm
    - opération choisie = 4 (débruiter)
    - fichier où sauver = lena_encoded_unnoised.pgm
    - opération choisie = 2 (décoder)
    - fichier où sauver = resultat.pgm
    - opération choisie = 0 (quitter le programme)
    -> observer que "resultat.pgm" affiche la même chose que "lena_128x128_64.pgm"


Notes sur l'éxécution:

    -> le bruit à utiliser ne dois pas dépaser 0.3 sinon la redondance n'est pas suffisante pour débrutier et décoder

    après "encoder" on peut uniquement "décoder" ou "bruiter" ou "réinitialiser".
    après "décoder" on peut uniquement "encoder" ou "réinitialiser".
    après "bruiter" on peut uniquement "débruiter" ou "réinitialiser" (attention -> pour bruiter, il faut avoir encodé)
    après "débruiter" on peut uniquement "bruiter" ou "décoder" ou "réinitialiser".

<<<<<<< HEAD
    dans le cas contraire, le programme se trouverait dans un état instable.
=======
    dans le cas contraire, le programme se trouverait dans un état instable.


A demander au prof demain:

    si on bruite et qu'on débruite tout de suite ca marche pas car c'est pas encodé
    si le seuil est supérieur à 0.3, ca marche pas ou pas bien
>>>>>>> 18ddc96dc08dc280381757a66a3a77737a231548
