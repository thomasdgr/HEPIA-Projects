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
#include "arrayNode.h"

arrayNode createArrayNode(int length){
    arrayNode content;
    content.length = length;
    content.array = malloc(length * (sizeof(node)));
	return content;
}

void freeArrayNode(arrayNode* content){
    if(content->array != NULL){
		free(content->array);
		content->array = 0;
	}
	content->length = -1;
}

void printArrayNode(arrayNode content){
	for(int i = 0; i < content.length; i++){
        printf("%d -> ", content.array[i].classe);
        for(int j = 0; j < 6; j++){
            printf("%d ", content.array[i].attributs[j]);
        }
        printf("\n");
    }
}

void printSingle(single * content, int size){
	for(int i = 0; i < size; i++){
        printf("%d -> %d\n", content[i].classe, content[i].attribut);
    }
}

single * nodeColumn(arrayNode content, int index){
	index = index - 1;
	single * array = malloc(content.length * (sizeof(single)));
	for(int i = 0; i < content.length; i++){
		array[i].classe = content.array[i].classe;
		array[i].attribut =  content.array[i].attributs[index];
	}
	return array;
}

arrayNode filter_arrayNode(arrayNode content, int index_coupe, int new_len, double coupe, bool lower){
	arrayNode res = createArrayNode(new_len);
	int j = 0;
	for(int i = 0; i < content.length; i++){
		if(lower){
			if((double)content.array[i].attributs[index_coupe-1] < coupe){
				res.array[j] = content.array[i];
				j++;
			}
		} else{
			if((double)content.array[i].attributs[index_coupe-1] > coupe){
				res.array[j] = content.array[i];
				j++;
			}
		}
    }
	return res;
}