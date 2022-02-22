#ifndef ERROR_H
#define ERROR_H

typedef enum error_code {
    ok,
    out_of_bounds,
    memory_error,
    uninitialized
    } error_code;

void error_code_display(error_code error, char* function_name);

#endif
