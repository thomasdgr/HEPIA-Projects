Projet d'algorithmes sur la recherche de motifs réalisé par Thomas Dagier et Dorian Bernasconi.

Exécution du projet:

    Pour trouver le nombre d'occurence du motif dans le texte:
        npx ts-node index.ts <motif> <algo> <path_to_text>
    Pour afficher les tableaux utilisés pour la recherche:
        npx ts-node index.ts <motif> <algo>
    
    Note: 
        - Pour Rabin-Karp, l'algorithme ne fonctionne que si le motif est une suite de chiffres
          exemple de commande : npx ts-node index.ts 1212 1 rkText.txt
        
        - Les tableaux attendus sont dans le fichier expected_array.txt
        
        - Les résultats attendus sont dans le fichier expected_data.txt
    
    Exemple:
        npx ts-node index.ts 1212 1 rkText.txt
        npx ts-node index.ts 1212 1

        npx ts-node index.ts bonsbonsbons 2 text.txt
        npx ts-node index.ts bonsbonsbons 2

        npx ts-node index.ts 1111abt1111ab 3 text.txt
        npx ts-node index.ts 1111abt1111ab 3

        npx ts-node index.ts wwww 4 text.txt
        npx ts-node index.ts wwww 4