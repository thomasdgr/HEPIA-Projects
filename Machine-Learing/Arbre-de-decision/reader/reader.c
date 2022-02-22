#include "reader.h"

arrayNode read(char *filename){
  int size = getFileSize(filename);
  arrayNode res = createArrayNode(size);
  FILE *f = fopen(filename, "r+");
  if (!f){
    printf("error while reading file: %s\n", filename);
    return res;
  }

  int ligne = 0;
  char *ligne_buffer = NULL;
  size_t num_buffer = 0;
  int count = 0;
  char *token;
  int i = 0;
  while ((ligne = getline(&ligne_buffer, &num_buffer, f)) > 0){
    node n;
    token = strtok(ligne_buffer, " ");
    count = 0;
    do{
      if ('0' <= token[0] && token[0] <= '9'){
        if(count == 0){
          n.classe = atoi(token);
        } else {
          n.attributs[count-1] = atoi(token);
        }
        count++;
      }
    } while ((token = strtok(NULL, " ")) != NULL);
    res.array[i] = n;
    i++;
  }
  free(ligne_buffer);
  fclose(f);
  return res;
}

int getFileSize(char * filename){
  int lines = 0;
  FILE *f = fopen(filename, "r+");
  while(!feof(f)){
    char ch = fgetc(f);
    if(ch == '\n')
    {
      lines++;
    }
  }
  fclose(f);
  return lines;
}
