/*********************************************************************************
            ____
           /____ \         | Projet :  Arbres de Décision, Gini
           | _ _`\|        |        
    .-.   `| O O |         | Auteurs : Thomas DAGIER, Gustavo PERTUZATI
    | |   (- /_  -)        |
    | |    |     |         | Descripition : Utiliser les notions abordées en
(___)  )\/  \_____/  ~\.   |                cours pour implémenter un arbre de
(___) . \   `         `\   |                décision binaire en C
 (__)-    ,/        (   |  |
      `--~|         |   |  |  Version : 1.0
          |         |   |  |  Date : 02/11/2021
*********************************************************************************/

// les commentaires sont dans les .h
#include "reader/reader.h"
#include "gini/gini.h"
#include "binaryTree/binaryTree.h"

int main(void){
    // variables à changer pour faire varier le résultat
    int profondeur = 4;
    double treshold = 0.01;
    int minimal_size = 1;

    // construction de l'arbre à partir du fichier d'entrainement
    arrayNode training_set = read("files/monks-1.train");
    arbre tree = create_elem(0, 0.0);
    build_tree(training_set, tree, profondeur, 0, treshold, -1, minimal_size);
    print_t(tree, profondeur);

    // vérification de la précision de l'arbre avec le fichier de test
    arrayNode testing_set = read("files/monks-1.test");
    printf("l'arbre de décision est fiable à %.2f%%\n", train(testing_set, tree));

    // suppresion des objets
    freeArrayNode(&training_set);
    free_tree(tree);
    freeArrayNode(&testing_set);

    return 0;
}