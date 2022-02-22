#ifndef OPTIONS_H
#define OPTIONS_H

#include "../error/error.h"

void info_node(const char* name);
void list_dir(char* name);
int copy_file(char* src, char* dst, bool aflag, bool fflag);
int copy_file_to_folder(char* src, char* dst, bool aflag, bool fflag);
int copy_folder(char* src, char* dst, bool aflag, bool fflag);

#endif
