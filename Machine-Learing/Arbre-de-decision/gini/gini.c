#include "gini.h"

double gini(single * data, int id, int nb_elem, double* coupe, int array[2][2]){
    double best_gini = 10.0;
    int num_class = 2;
    for(int i = 1; i <= getSizeFromId(id) - 1; i++){
        // création du tableau
        int** kek = calloc(0, num_class * sizeof(int*));
        kek[0] = calloc(0, num_class * 2 * sizeof(int));
        for (int k = 0; k < num_class; k++) {
            kek[k] = kek[0] + k * 2;
        }
        // remplissage du tableau selon la coupe
        for(int k = 0; k < nb_elem; k++){
            if((double)data[k].attribut < (double)i+0.5){
                kek[data[k].classe][0] += 1;
            } else{
                kek[data[k].classe][1] += 1;
            }
        }
        // calcul de Gini

        if(kek[0][0] + kek[1][0] == 0 || kek[0][1] + kek[1][1] == 0){
            free(kek[0]);
            free(kek);
            continue;
        }

        double p_0 = (double)kek[0][0] / (double)(kek[0][0] + kek[1][0]);
        double p_1 = (double)kek[1][0] / (double)(kek[0][0] + kek[1][0]);
        double x = 1 - pow(p_0, 2) - pow(p_1, 2);

        p_0 = (double)kek[0][1] / (double)(kek[0][1] + kek[1][1]);
        p_1 = (double)kek[1][1] / (double)(kek[0][1] + kek[1][1]);
        double y = 1- pow(p_0, 2) - pow(p_1, 2);
        
        double gini_pondere = x * (((double)kek[0][0]+(double)kek[1][0]) / (double)nb_elem) + y * (((double)kek[0][1]+(double)kek[1][1]) / (double)nb_elem);

        if(gini_pondere < best_gini){
            best_gini = gini_pondere;
            *coupe = (double)i + 0.5;
            for(int k = 0; k < 2; k++){
                for(int l = 0; l < 2; l++){
                    array[k][l] = kek[k][l];
                }
            }
        }
        free(kek[0]);
        free(kek);
    }
    return best_gini;
}

int getSizeFromId(int id){
    int size = 0;
    switch(id){
        case 1 : size = 3; break;
        case 2 : size = 3; break; 
        case 3 : size = 2; break; 
        case 4 : size = 3; break; 
        case 5 : size = 4; break; 
        case 6 : size = 2; break; 
        default: printf("wrong value for id\n");
    }
    return size;
}

int best_cut(int size, arrayNode kek, double* best_gini, double* coupe, int array[2][2]){
    double current_cut;
    int res[2][2];
    int index_coupe = 0;
    for(int i = 0; i < size; i++){
        single * kek_aX = nodeColumn(kek, i+1);
        double current_gini = gini(kek_aX, i+1, kek.length, &current_cut, res);
        if(current_gini < *best_gini){
            *best_gini = current_gini;
            *coupe = current_cut;
            for(int i = 0; i < 2; i++){
                for(int j = 0; j < 2; j++){
                    array[i][j] = res[i][j];
                }
            }
            index_coupe = i+1;
        }
        free(kek_aX);
    }
    return index_coupe;
}