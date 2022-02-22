#ifndef TOOLS_H
#define TOOLS_H

#include "../color/color.h"

char** convert_input_to_array(char* s);
void remove_leading_trailing_spaces(char* s);

char* get_cmd_from_array(char** array, const char* pattern);
char* get_second_cmd_from_array(char** array);
bool detect_pattern(char** array, const char* pattern);

char* get_file_from_redirection(char** array);

void get_args_from_pipe(char** array, char* name1, char* name2, char* s_arg1, char* s_arg2);

char* get_output_job(int i, int j, char* status);

#endif
