#include "error.h"


// retourne 0 si la source est un fichier regulier
//          1 si la source est un lien
//          2 si la source est un dossier
//         -1 sinon
int detect_input_type(char* src){
    struct stat s;
    lstat(src, &s);
    if(S_ISREG(s.st_mode)){
        return 0;
    } else if(S_ISLNK(s.st_mode)){
        return 1;
    } else if(S_ISDIR(s.st_mode)){
        return 2;
    } else {
        return -1;
    }
}

// concatène le nom d'un fichier/dossier avec sa source complète
char* get_complete_path(char* src, char* current_name){
    char* path = malloc(PATH_MAX * sizeof(char));
    strcat(path, src);
    strcat(path, current_name);
    return path;
}

// si le dossier de destination est "dest/" on ne fait rien, par contre s'il est "dest" on lui ajoute un "/" à la fin
void detect_shape_folder(char* path){
    char* tmp = path;
    if(tmp[(strlen(tmp)-1)] != '/'){
        char ch = '/';
        strncat(tmp, &ch, 1); 
    }
    path = tmp;
}

// vérifie que le dossier de destination ne se trouve pas dans le dossier source
void check_subdirectory(char* src, char *dst){
    char buf[PATH_MAX];
    char buf2[PATH_MAX];
    char* input = realpath(src, buf);
    if(input){
        char* output = realpath(dst, buf2);
        if(output){
            if(strstr(output, input) != NULL) {
                printf("destination folder can't be in source folder\n");
                exit(EXIT_FAILURE);    
            }
        } else {
            printf("Failed to get realpath of '%s': %s\n", dst, strerror(errno));
            exit(EXIT_FAILURE); 
        }
    } else {
        printf("Failed to get realpath of '%s': %s\n", src, strerror(errno));
        exit(EXIT_FAILURE); 
    }
}

// regarde si le fichier existe
bool file_exist(char* src){
    return access(src, F_OK) == 0;
}

// regarde si la date de la source est plus ancienne que celle de la destination
bool compare_file_date(char* src, char* dst){
    struct stat s,d;    
    stat(src,&s);
    stat(dst,&d);
    return s.st_mtime > d.st_mtime;
}

// regarde si on peut écraser le fichier source dans la destination
bool overwrite_file(char* src, char* dst){
    if(file_exist(dst)){
        struct stat s,d;
        stat(src,&s);
        stat(dst,&d);
        return (d.st_size != s.st_size) ? compare_file_date(src,dst) : false; 
        /*if(d.st_size != s.st_size){
            return compare_file_date(src,dst);
        } else{
            return false;
        }*/
    }
    return true;
}