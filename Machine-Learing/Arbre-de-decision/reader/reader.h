#ifndef READER_H_
#define READER_H_

#include "../arrayNode/arrayNode.h"

// lecture d'un fichier et stockage des données dans un objet arrayNode
arrayNode read(char *filename);

// retourne le nombre de noeuds d'un fichier
int getFileSize(char * filename);

#endif
