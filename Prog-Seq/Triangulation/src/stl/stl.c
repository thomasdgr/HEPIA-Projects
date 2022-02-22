/**********************************************************************************************************************************************************************************************************************************\
			____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |  
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              | 
    | |    |     |               |  Descripition : Librairie stl qui permet de créer et écrire dans un fichier .stl
 __/  |    | \__/|               |                 des points en 3D après triangulation
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |  
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020		
                                 
\**********************************************************************************************************************************************************************************************************************************/
#include "stl.h"

stl_file stl_file_create(char *filename, char *name){
  stl_file s;
  FILE *f = fopen(filename, "w+");
  assert(f);
  assert(!(name == NULL));
  s.file = f;
  s.name = name;
  fprintf(s.file, "solid %s\n", s.name);
  return s;
}

void stl_file_close(stl_file *s){
  assert(s->file && "file doesn't exist");
  fprintf(s->file, "endsolid %s\n", s->name);
  fclose(s->file);
  s->name = NULL;
}

void stl_file_write_triangle(stl_file *s, triangle *t){
  point_3d normal = triangle_compute_normal(t);
  point_3d_normalize_in_place(&normal);
  fprintf(s->file,"facet normal %e %e %e\n  outer loop\n", normal.x, normal.y, normal.z);
  fprintf(s->file, "    vertex %e %e %e\n",t->v1.x, t->v1.y, t->v1.z );
  fprintf(s->file, "    vertex %e %e %e\n",t->v2.x, t->v2.y, t->v2.z );
  fprintf(s->file, "    vertex %e %e %e\n",t->v3.x, t->v3.y, t->v3.z );
  fprintf(s->file, "  endloop\nendfacet\n");
}

void stl_file_create_and_write(char *filename, char *name, triangle *t, int num_triangles){
  stl_file a = stl_file_create(filename, name);
  for (int i = 0; i < num_triangles; i++){
    stl_file_write_triangle(&a, t+i);
  }
  stl_file_close(&a);
}
