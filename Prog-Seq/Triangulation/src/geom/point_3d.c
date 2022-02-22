/**********************************************************************************************************************************************************************************************************************************\
			____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |  
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              | 
    | |    |     |               |  Descripition : Librairie de point_3d pour construire des triangles et
 __/  |    | \__/|               |                 faire des calculs sur des points à trois coordonnées
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |  
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	11/03/2020		
                                 
\**********************************************************************************************************************************************************************************************************************************/
#include "point_3d.h"

point_3d point_3d_create(double x, double y, double z){
    point_3d p = {x,y,z};
    return p;
}

void point_3d_add_inplace(point_3d *p1, point_3d *p2){
    p1->x += p2->x;
    p1->y += p2->y;
    p1->z += p2->z;
}

void point_3d_sub_inplace(point_3d *p1, point_3d *p2){
    point_3d value = point_3d_scale(p2, -1);
    point_3d_add_inplace(p1, &value);
}

void point_3d_scale_inplace(point_3d *p1, double a){
    p1->x *= a;
    p1->y *= a;
    p1->z *= a;
}

point_3d point_3d_add(point_3d *p1, point_3d *p2){
    point_3d point = *p1;
    point_3d_add_inplace(&point, p2);
    return point;
}

point_3d point_3d_sub(point_3d *p1, point_3d *p2){
    point_3d point = *p1;
    point_3d_sub_inplace(&point, p2);
    return point;
}

point_3d point_3d_scale(point_3d *p1, double a){
    point_3d point = *p1;
    point_3d_scale_inplace(&point, a);
    return point;
}

double compute_norm(point_3d *p){
    return sqrt(((p->x)*(p->x))+((p->y)*(p->y))+((p->z)*(p->z)));
}

double compute_distance(point_3d *p1, point_3d *p2){
    point_3d point = point_3d_sub(p1, p2);
    return compute_norm(&point);
}

void print_point(point_3d *p){
    printf("p.x : %f\n", p->x);
    printf("p.y : %f\n", p->y);
    printf("p.z : %f\n", p->z);
}

void point_3d_normalize_in_place(point_3d *p){
    double norme = compute_norm(p);
    if (norme != 0.0){
        point_3d_scale_inplace(p, (1.0/norme));
    }
}

point_3d point_3d_normalize(point_3d *p){
    point_3d point = *p;
    point_3d_normalize_in_place(&point);
    return point;
}

point_3d point_3d_vector_product(point_3d *p1, point_3d *p2){
    point_3d point;
    point.x = (p1->y * p2->z) - (p1->z * p2->y);
    point.y = (p1->z * p2->x) - (p1->x * p2->z);
    point.z = (p1->x * p2->y) - (p1->y * p2->x);
    return point;
}
