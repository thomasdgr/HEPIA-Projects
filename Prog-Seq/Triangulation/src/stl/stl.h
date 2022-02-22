#ifndef STL_H
#define STL_H

#include "../geom/triangle.h"
#include "assert.h"

typedef struct {
    char *name;
    FILE *file;
} stl_file;

stl_file stl_file_create(char *filename, char *name);
void stl_file_close(stl_file *s);
void stl_file_write_triangle(stl_file *s, triangle *t);
void stl_file_create_and_write(char *filename, char *name, triangle *t, int num_triangles);

#endif