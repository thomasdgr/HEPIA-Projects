Réponses aux questions du tp:

1) La valeur retournée par le read() est 26 car c'est le nombre max qui peut être lu (puisque le buffer fait une taille de 26 octets).

2) La commande cat utilisée ici est placée dans une boucle qui s'arrête quand l'entièreté du buffer est lue ( read() dans une boucle while() ). Sauf que notre buffer est circulaire, on ne peut donc pas terminer la lecture. Si on utilise la commande strace, on voit que la commande "cat /dev/abcd" fait un read() puis un write() sur la sortie standard on observe donc que c'est une boucle infinie.

3) Si on fait 2 open() sur on créé 2 entrées dans la table des canaux. On a donc 2 descripteurs de fichiers ce qui signifie que chaque open() possède son propre offset. La lecture n'est donc pas perturbée.

4) On observe que les 26 derniers caractères ont pu être écrit correctement mais que les autres n'ont pas été écrit puisque le buffer est plein.


5) Avec la commande strace on peut voir en détail comment se passe cette étape. On écrit 26 la première fois. La valeur de retour correspond à la partie restante. Par la suite, on replace le pointeur à 0 et on réécrit la partie restante qui est de 24 char. Comme il demmande à écrire 24 et qu'il peut le faire, on peut en conclure que tout fonctionne.

6) La commande fait effectivement plusieurs appels systemes :
    un premier, write(1, "...", 46) -> nous retourne 26 soit la taille du buffer
    un second, write(1, "...", 20) -> nous retourne 20, on a donc réussi à tout écrire sans soucis avec 2 appels.

7) Avec la commande write(), on n'aura pas de problèmes de lecture ni d'écriture puisque l'on va simplement écrire par dessus des données éxistantes dans notre buffer de 26 éléments. Cependant, on ne peut pas garantir que le résultat (ou en tout cas le contenu du buffer) soit celui attendu par l'utilisateur. De plus, comme décrit dans la question 3, si on fait plusieurs open() on ne partage pas l'offset donc on garanti l'atomicité même si le comportement peut ne pas être cohérent.