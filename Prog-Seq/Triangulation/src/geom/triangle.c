/**********************************************************************************************************************************************************************************************************************************\
			 ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |  
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              | 
    | |    |     |               |  Descripition : Création et manipulation de triangle à partir de la  
 __/  |    | \__/|               |                 librairie point_3d
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |  
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	11/03/2020		
                                 
\**********************************************************************************************************************************************************************************************************************************/
#include "triangle.h"

triangle triangle_create(point_3d v1, point_3d v2, point_3d v3){
    triangle t = {v1,v2,v3};
    return t;
}

point_3d triangle_compute_normal(triangle *t){
    point_3d v12 = point_3d_sub(&(t->v2),&(t->v1));
    point_3d v13 = point_3d_sub(&(t->v3),&(t->v1));
    return point_3d_vector_product(&v12, &v13);;
}

double triangle_compute_area(triangle *t){
    point_3d v_normal = triangle_compute_normal(t);
    double area = compute_norm(&v_normal)/2;
    return area;
}
