#include "binaryTree.h"

void free_tree(arbre tree){
    if (tree != NULL){
        free_tree(tree->tab[0]);
        free_tree(tree->tab[1]);
        free(tree);
    }
}


elem * create_elem(double coupe, int index_cut){
    elem * e = calloc(1,sizeof(elem));
    e->coupe = coupe;
    e->index_coupe = index_cut;
    e->tab[0] = NULL;
    e->tab[1] = NULL;
    e->classe = -1;
    return e; 
}

void build_tree(arrayNode kek, elem * node, int profondeur_max, int profondeur, double pourcentage_min, int id_node, int minimal_size){
    if(profondeur > profondeur_max){
        return;
    }

    int array[2][2];
    double coupe;
    double best_gini = 10.0;

    int index_cut = best_cut(6, kek, &best_gini, &coupe, array);
    node->classe = id_node;
    node->coupe = coupe;
    node->index_coupe = index_cut;

    arrayNode kek_gauche = filter_arrayNode(kek, index_cut, array[0][0] + array[1][0], coupe, true);
    arrayNode kek_droite = filter_arrayNode(kek, index_cut, array[0][1] + array[1][1], coupe, false);


    // pourcentage enfant gauche
    if(MIN(((double)array[0][0] / ((double)array[0][0] + (double)array[1][0])),((double)array[1][0] / ((double)array[0][0] + (double)array[1][0]))) >= pourcentage_min && (array[0][0] + array[1][0]) >= minimal_size){
        node->tab[0] = create_elem(coupe, index_cut);
        build_tree(kek_gauche, node->tab[0], profondeur_max, profondeur+1, pourcentage_min, 1, minimal_size);
    }
    // pourcentage enfant droite
    if(MIN(((double)array[0][1] / ((double)array[0][1] + (double)array[1][1])),((double)array[1][1] / ((double)array[0][1] + (double)array[1][1]))) >= pourcentage_min && (array[0][1] + array[1][1]) >= minimal_size){
        node->tab[1] = create_elem(coupe, index_cut);
        build_tree(kek_droite, node->tab[1], profondeur_max, profondeur+1, pourcentage_min, 0, minimal_size);
    }

    freeArrayNode(&kek_gauche);
    freeArrayNode(&kek_droite);
}

int get_class(node n, elem*tree){
    int classe = -1;
    if((double)n.attributs[tree->index_coupe-1] < tree->coupe){
        if(tree->tab[0] != NULL){
            classe = get_class(n, tree->tab[0]);
        } else{
            return 1;
        }
    } else{
        if(tree->tab[1] != NULL){
            classe = get_class(n, tree->tab[1]);
        } else{
            return 0;
        }
    }
    return classe;
}

double train(arrayNode content, elem* tree){
    int count = 0;
    for(int i = 0; i < content.length; i++){
        int classe = get_class(content.array[i], tree);
        if(classe == content.array[i].classe){
            count++;
        }
    }
    return ((double)count / (double)content.length) * 100;
}

int _print_t(elem *tree, int is_left, int offset, int depth, char s[255][255]){
    char b[20];
    int width = 5;

    if(!tree){
        return 0;
    }
    sprintf(b, "  a%d   \n", tree->index_coupe);

    int left  = _print_t(tree->tab[0], 1, offset, depth + 1, s);
    int right = _print_t(tree->tab[1], 0, offset + left + width, depth + 1, s);

    for(int i = 0; i < width; i++){
        s[2 * depth][offset + left + i] = b[i];
    }
    if(depth && is_left){
        for (int i = 0; i < width + right; i++){
            s[2 * depth - 1][offset + left + width/2 + i] = '-';
        }
        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';
    } else if(depth && !is_left){
        for (int i = 0; i < left + width; i++){
            s[2 * depth - 1][offset - width/2 + i] = '-';
        }
        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
    return left + width + right;
}

void print_t(elem *tree, int depth){
    char s[255][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++){
        for(int j = 0; j < depth; j++){
            printf("\t"); 
        }
        printf("%s\n", s[i]);
    }
}