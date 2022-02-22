#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// type permettant de stocker un arbre dynamique
typedef struct _node
{
   char lettre;
   struct _node* point; // gauche
   struct _node* trait; // droite
} node;

typedef node* arbre;

//----------------------------------------------------------
// procedure imprimant l'arbre verticalement de mani�re   --
// selon un parcours DRG (trait - racine - point)         --
//----------------------------------------------------------
void print(arbre tree,int niv)
{
  if (niv <= 0) niv = 1;

  if(tree != NULL)
  {
    print(tree->trait, niv + 1);
    for (int i = 0; i < niv; i++)
    {
        printf("    ");
    }
    printf("%c\n",tree->lettre);
    print(tree->point, niv + 1);
  }
}

//----------------------------------------------------------
// procedure imprimant le tableau de code morse         --
//----------------------------------------------------------
void print_mat(int n, int m, char alphabet_morse[n][m])
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
       if (alphabet_morse[i][j] == '\0') break;
       printf("%c", alphabet_morse[i][j]);
    }
     printf("\n");
  }
}

//----------------------------------------------------------
// procedure traduisant un code morse en lettre
//----------------------------------------------------------
char decoder(char* code,arbre tree)
{
   node *tmp = tree;
   int lg = strlen(code);
   for (int i = 0; i < lg; i++)
   {
     if(code[i] == '-')
     {tmp = tmp->trait;}
     else if(code[i] == '.')
     {tmp = tmp->point;}
     else{printf(" ");}
   }
   return tmp->lettre;
}

//-----------------------------------------------------------
// lit un fichier encod� avec le code et imprime � l'�cran --
// le texte d�cod�                                         --
//-----------------------------------------------------------
void decoder_fichier(char* filename,arbre tree)
{
   // lecture d'un mot de caract�res dans 'A'..'Z'
   FILE* fp = fopen(filename,"r");
   assert(NULL != fp);
   char *line_buff = NULL;
   size_t line_buff_size = 0;
   while (getline(&line_buff, &line_buff_size, fp) >= 0)
   {
     char *token = strtok(line_buff, " ");
     while (token != NULL)
     {
       char lettre = decoder(token, tree);
       printf("%c", lettre);
       token = strtok(NULL, " \n");
     }
     printf("\n");
   }
   free(line_buff);
   fclose(fp);
}

//-----------------------------------------------------------
// lit un fichier encod� avec le code et imprime � l'�cran --
// le texte d�cod�                                         --
//-----------------------------------------------------------
void encoder_fichier(char* filename,int n,int m,char alphabet_morse[n][m])
{
   // lecture d'un mot de caract�res dans 'A'..'Z'
   FILE* fp = fopen(filename,"r");
   assert(NULL != fp);
   while (!feof(fp)) {
      char ch = (char)fgetc(fp);
      switch(ch)
      {
        case ' ':
          printf("/");
          break;
        case '\n':
          printf("\n");
          break;
        default:
          for (int i = 0; i < n; i++)
          {
            if (ch == alphabet_morse[i][0])
            {
              int j = 1;
              while (alphabet_morse[i][j] != '\0')
              {
                printf("%c", alphabet_morse[i][j]);
                j++;
              }
              printf(" ");
              break;
            }
          }
          break;
      }
   }
   fclose(fp);
}

//------------------------------------------------------------------
// procedure ins�rant une lettre d�finie par son code morse dans  --
// l'arbre. L'arbre est construit au fur et � mesure des besoins. --
//------------------------------------------------------------------
void placer(char* chaine,arbre* tree)
{
   arbre tmp = *tree;
   int length = strlen(chaine);
   for (int i = 1; i < length; i++)
   {
     if(chaine[i] == '.')
     {
       if(tmp->point == NULL)
       {
         tmp->point = calloc(1,sizeof(node));
         tmp->point->lettre = '?';
       }
       tmp = tmp->point;
     }
     else
     {
       if(tmp->trait == NULL)
       {
         tmp->trait = calloc(1,sizeof(node));
         tmp->trait->lettre = '?';
       }
       tmp = tmp->trait;
     }
   }
   tmp->lettre = chaine[0];
}

//----------------------------------------------------------
// procedure lisant le fichier code-morse.txt et cr�ant   --
// le tableau � deux dimensions correspondant             --
//----------------------------------------------------------
void table_build(char* filename,int n,int m,char alphabet_morse[n][m])
{
   FILE* fp = fopen(filename,"r");
   char *line_buff = NULL;
   size_t line_buff_size = 0;
   assert(NULL != fp);
   int i = 0;
   while (getline(&line_buff, &line_buff_size, fp) >= 0)
   {
     char *token = strtok(line_buff, "\n\t\f");
     int lg = strlen(token);
     for (int j = 0; j <= lg; j++)
     {
       alphabet_morse[i][j] = token[j];
       if (j == lg) alphabet_morse[i][j] = '\0';
     }
     i++;
   }
   free(line_buff);
   fclose(fp);
}

//----------------------------------------------------------
// procedure lisant le fichier code-morse.txt et cr�ant   --
// l'arbre binaire correspondant                          --
//----------------------------------------------------------
arbre arbre_build(char* filename)
{
   arbre tree = calloc(1,sizeof(node));
   tree->lettre = '.';

   FILE* fp = fopen(filename,"r");
   char *line_buff =NULL;
   size_t line_buff_size = 0;

   assert(NULL != fp);

   while (getline(&line_buff, &line_buff_size, fp) >= 0)
   {
     char *token = strtok(line_buff, "\n\t\f");
     placer(token, &tree);
   }
   free(line_buff);
   fclose(fp);
   return tree;
}

//----------------------------------------------------------
// procedure libérant les mémoires alloués pour l'arbre   --
//----------------------------------------------------------
void free_tree(arbre tree)
{
  if (tree != NULL)
  {
    free_tree(tree->point);
    free_tree(tree->trait);
    free(tree);
  }
}

//----------------------------------------------------------
// programme principal                                    --
//----------------------------------------------------------
int main(int argc, char** argv)
{
   arbre tree = arbre_build("code-morse.txt");
   char alphabet_morse[26][6];
   table_build("code-morse.txt",26,6,alphabet_morse);
   print(tree,1);   // impression de l'arbre
   if (2 == argc)
   {
      decoder_fichier(argv[1],tree);
      printf("\n");
   }
   free_tree(tree);
   print_mat(26,6,alphabet_morse); //impression tableau mat-morse
   if (3 == argc)
   {
      encoder_fichier(argv[2],26,6,alphabet_morse);
      printf("\n");
   }
   return 0;
}
