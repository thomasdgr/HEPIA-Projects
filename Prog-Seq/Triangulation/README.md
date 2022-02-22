Projet de Triangulation du M Park à Genève :
    Récéption d'un fichier .las, lecture des points, triangulation en appliquant l'algorithme de Bowyer-Watson
    inspiré par Delaunnay et écriture du résultat dans un fichier .stl
    
    Réalisé entre le 18 Décembre 2019 et le 15 Mars 2020 par Thomas Dagier 
    dans le cadre du cours de Programmation Séquentielle
    
    Execution du projet:
        A la racine du dossier : 
            éxécuter le projet : make main
                                ./main <fichier_input.las> <pourcentage de séléction (entre 0 et 1)> <fichier_output.stl> <'list'/'vector'>
                                -> le dernier paramètre permet de choisir entre une triangulation 
                                   utisant les listes chainées ou une triangulation utilisant les tableaux
        
            éxécuter les tests : make test
            
            en cas de problèmes lors du make (ne devrait pas arriver) : make clean 
    