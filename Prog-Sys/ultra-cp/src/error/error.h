#ifndef ERROR_H
#define ERROR_H

#define _GNU_SOURCE

#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int detect_input_type(char* name);
char* get_complete_path(char* name, char* current_name);
void detect_shape_folder(char* path);
bool file_exist(char* name);
bool compare_file_date(char* src, char* dst);
bool overwrite_file(char* src, char* dst);
void check_subdirectory(char* src, char *dst);

#endif