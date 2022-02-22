/*******************************************************************************\
		     ____
           /____ \         | Projet : Ultra-cp (insipré du programme rsync), mise 
           | _ _`\|        |          en oeuvre d'un programme permettant de faire
    .-.    | O O  |        |          des backups d'architecture de fichiers.     
    | |  (-   /_  -)       | 
    | |    |     |         | Auteur : Thomas DAGIER (encadré par Guillaume Chanel)
 __/  |    | \__/|         |    
(___) \.  _.\__. `\___     | Objectifs : Mainpuler des fichiers, parcourir des   
(___)  )\/  \_____/  ~\.   |             architectures de dossiers, manipuler des
(___) . \   `         `\   |             liens, et manipuler des inodes.          
 (__)-    ,/        (   |  |
      `--~|         |   |  | Version : 2.0                                       
          |         |   |  | Date : 19/01/2021                                   

\*******************************************************************************/

#include "options/options.h"

int main(int argc, char* argv[]){
    // listing de fichier
    if(argc == 2){
        char* src = argv[1];
        if(detect_input_type(src) == 2){
            if(src[(strlen(src)-1)] != '/'){
                char ch = '/';
                strncat(src, &ch, 1); 
            }
            list_dir(src);
        } else {
            info_node(src);
        }
    // backup de dossiers et fichiers
    } else if(argc > 2){

        char* src = malloc(PATH_MAX * sizeof(char));
        char* dst = malloc(PATH_MAX * sizeof(char));
        bool aflag = false;
        bool fflag = false;

        // on prend chaque argument un par une
        for(int i = 1; i < argc-1; i++){
            strcpy(src, argv[i]);
            strcpy(dst, argv[argc-1]);

            // on regarde si c'est une option (dans ce cas, on passe à l'argument suivant)
            if(strcmp(src, "-a") == 0){
                aflag = true;
                continue;
            } else if(strcmp(src, "-f") == 0){
                fflag = true;
                continue;
            } else if(strcmp(src, "-af") == 0){
                aflag = true;
                fflag = true;
                continue;
            }

            // si l'argument est un dossier
            if(detect_input_type(src) == 2){
                // adaptation de la syntaxe (un folder peut etre lu comme "dest" ou "dest/")
                detect_shape_folder(src);
                detect_shape_folder(dst);

                // autrement, on copie un dossier dans un autre
                copy_folder(src, dst, aflag, fflag);
            
            // si l'argument n'est pas un dossier mais que la destination en est une
            } else if(dst[(strlen(dst)-1)] == '/'){

                // création du dossier de destination (sil n'existe pas)
                mkdir(dst,0777);

                // copie du fichier dans le dossier
                copy_file_to_folder(src, dst, aflag, fflag);

            // si l'argument est un fichier et que la source n'en est pas un            
            } else if(detect_input_type(src) == 0){
                // on regarde si la copie fichier vers fichier est possible (en fonction des flags et du nombre d'argument)
                if(detect_input_type(dst) == 2 || 
                    (detect_input_type(dst) == 0 && ( 
                        (argc < 5 && ( (aflag == true) || (fflag == true) ) ) ||
                        (argc < 4) ) ) ){
                    
                    //copie du fichier vers un autre
                    copy_file(src, dst, aflag, fflag);
                } else{
                    printf("impossible to copy content of multiple files and/or folder into one output file\n");
                    break;
                }
            } else {
                printf("%s not found : no such file or directory\n",src);
                break;
            }
        }        
        free(src);
        free(dst);
    }
     else {
        printf("one argument required (file path or folder path)\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}