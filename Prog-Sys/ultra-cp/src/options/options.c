#include "options.h"

// affichage des infos d'un fichier
void info_node(const char* name){
    struct stat fileStat;
    
    if(lstat(name, &fileStat) < 0){
        printf("Failed to stat '%s': %s\n", name, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if(S_ISDIR(fileStat.st_mode)){
        printf("d"); // dir
    } else if(S_ISLNK(fileStat.st_mode)){
        printf("l"); // link
    } else if(S_ISREG(fileStat.st_mode)){
        printf("-");
    } else if(S_ISCHR(fileStat.st_mode)){
        printf("c"); // char file
    } else if(S_ISBLK(fileStat.st_mode)){
        printf("b"); // block file
    } else if(S_ISFIFO(fileStat.st_mode)){
        printf("f"); // fifo
    } else if(S_ISSOCK(fileStat.st_mode)){
        printf("s"); // socket
    } else {
        printf("Unknown type of file : '%s': %s\n", name, strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-"); // user read
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-"); // user write
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-"); // user exec
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-"); // group read
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-"); // group write
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-"); // group exec
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-"); // other read
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-"); // other write
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-"); // other exec

    printf("\t %ld\t%s\t%s\n", fileStat.st_size, strtok(ctime(&fileStat.st_mtime), "\n"), name);
}

// affichage récursif de chaque fichier et dossiers d'un dossier source et de leurs infos
void list_dir(char* name){
    DIR *root_directory = opendir(name);

    if(!root_directory){
      printf("Failed to open '%s': %s\n", name, strerror(errno));
      exit(EXIT_FAILURE);
    }

    struct dirent *current;
    char* current_name = malloc(PATH_MAX * sizeof(char));
    char* path = malloc(PATH_MAX * sizeof(char));

    // pour chaque fichiers / dossiers de la source
    while((current = readdir(root_directory)) != NULL){
        current_name = current->d_name;

        // si l'élément actuel est un dossier...
        if(current->d_type & DT_DIR){
            // ... et qu'il n'est ni "." ni ".."
            if(strcmp(current_name, "..") != 0 && strcmp(current_name, ".") != 0){
                // on met a jour le chemin pour lister le contenu de ce dossier
                strcpy(path, name);
                strcat(path, current_name);
                strcat(path, "/");

                // on affiche les infos du dossier
                info_node(path);

                // on rapelle la fonction pour parcourir chaque élément de ce dossier
    	        list_dir(path);
            }
        // si l'élément actuel est un fichier
        } else{
            // on met a jour le chemin 
            strcpy(path, name);
            strcat(path, current_name);

            // on affiche les infos du fichier
            info_node(path);
        }
    }
    if(closedir(root_directory)){
      printf("Failed to close '%s': %s\n", name, strerror(errno));
      exit(EXIT_FAILURE);
    }
    free(path);
}

// copie d'un fichier avec appels systèmes
int copy_file(char* src, char* dst, bool aflag, bool fflag){
    // on regarde si on a le droite d'écraser le fichier (en fonction de la date et de la taille des 2 fichiers)
    // retourne vrai si les deux fichiers ne sont pas les mêmes
    bool isOverwrite = overwrite_file(src,dst);

    // si on a l'option "-f" et que la source est un lien
    if(fflag && detect_input_type(src) == 1){

        // on supprime le fichier qui n'est pas un lien pour copier le même fichier mais en tant que lien cett fois
        if(file_exist(dst)){
            int del = remove(dst);
            if(del){
                printf("Failed to delete dst '%s': %s\n", dst, strerror(errno));
                exit(EXIT_FAILURE); 
            }
        }

        // on copie le fichier comme un véritable lien
        char buf[PATH_MAX];
        char* input = realpath(src, buf);
        if(input == NULL){
            printf("Failed to read src '%s': %s\n", src, strerror(errno));
            exit(EXIT_FAILURE); 
        }        
        return symlink(buf, dst);
    }

    // ouverture du fichier source avec appels systèmes et gestion des erreurs
    int input = open(src, O_RDONLY);
    if(input < 0){
        printf("Failed to open src '%s': %s\n", src, strerror(errno));
        exit(EXIT_FAILURE);
    } else if(detect_input_type(src) == -1){
        printf("File %s is neither file nor folder nor link\n", src);
        exit(EXIT_FAILURE);
    }
    struct stat fileStat;
    stat(src, &fileStat);
    
    // si on doit écrire sur le nouveau fichier
    if(isOverwrite){
        
        // ouverture du fichier destination avec appels systèmes et gestion des erreurs
        int output = 0;
        if(file_exist(dst)){
            output = open(dst, O_WRONLY, fileStat.st_mode);
        } else {
            output = open(dst, O_WRONLY | O_CREAT | O_EXCL, fileStat.st_mode);
        }
        if(output < 0){
        printf("Failed to open dst '%s': %s\n", dst, strerror(errno));
        exit(EXIT_FAILURE);
        } else if(detect_input_type(dst) == -1){
            printf("File %s is neither file nor folder nor link\n", dst);
            exit(EXIT_FAILURE);
        }
        char* buff = malloc(sizeof(char) * 65535);

        // écriture du contenu de la source dans la destination et gestion des erreurs
        for(int i = 0; i < fileStat.st_size; i++){
            if(read(input, buff, 1) < 0){
                printf("Failed to read src '%s': %s\n", src, strerror(errno));
                exit(EXIT_FAILURE); 
            }
            if(write(output, buff, 1) < 0){
                printf("Failed to write dst '%s': %s\n", dst, strerror(errno));
                exit(EXIT_FAILURE); 
            }
        }
        free(buff);

        // ajout des droits de la source sur la destination
        chmod(dst,fileStat.st_mode);
        if(close(output) < 0){
            printf("Failed to close dst '%s': %s\n", dst, strerror(errno));
            exit(EXIT_FAILURE); 
        }

    // si on a l'option "-a" et que l'on ne remplace pas le fichier
    } else if(aflag){
        chmod(dst,fileStat.st_mode);
    }
    if(close(input) < 0){
        printf("Failed to close src '%s': %s\n", dst, strerror(errno));
        exit(EXIT_FAILURE); 
    }
    return 1;
}

// copie d'un seul fichier dans un dossier
int copy_file_to_folder(char* src, char* dst, bool aflag, bool fflag){
    strcat(dst,basename(src));
    copy_file(src,dst,aflag,fflag);
    return 1;
}

// copie d'un dossier et de son contenu dans un autre dossier (même concept que list_dir())
int copy_folder(char* src, char* dst, bool aflag, bool fflag){
    DIR* input = opendir(src);
    if(!input){
      printf("Failed to open '%s': %s\n", src, strerror(errno));
      exit(EXIT_FAILURE);
    }

    // création du dossier de destination et vérification qu'il ne se situe pas dans le dossier src
    // (autrement on quitte pour éviter un boucle infinie et on supprime le dossier de destination)
    mkdir(dst,0777);
    check_subdirectory(src,dst);

    struct dirent* current = readdir(input);
    char* content = malloc(PATH_MAX * sizeof(char));
    char* tmp = malloc(PATH_MAX * sizeof(char));

    // pour chaque fichiers / dossiers de la source
    while(current != NULL){

        // si l'élément actuel n'est ni "." ni ".."
        if(strcmp(current->d_name,".") != 0 && strcmp(current->d_name,"..") != 0 ){

            // on met a jour les chemins de la source et de la destination
            strcpy(content,src);
            strcat(content, current->d_name);
            strcpy(tmp, dst);
            strcat(tmp, current->d_name);

            // si la source est un dossier...
            if(detect_input_type(content) == 2){

                // on met a jour les chemins de la source et de la destination
                strcat(content, "/");
                strcat(tmp, "/");

                // on rapelle la fonction pour parcourir chaque élément de ce dossier
                copy_folder(content, tmp, aflag, fflag);

            // ... autrement, on copie l'élément vers son dossier de destination
            } else {
                copy_file(content, tmp, aflag, fflag);
            }
        }
        current = readdir(input);
    }
    free(content);
    free(tmp);
    closedir(input);
    return 1;
}