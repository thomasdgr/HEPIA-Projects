/**********************************************************************************************************************************************************************************************************************************\
			       ____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              |
    | |    |     |               |  Descripition : Triangulation des points suivant la procédure de Delaunay
 __/  |    | \__/|               |                 et l'algorithme de Bowyer-Watson en utilisant des listes de points
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         | 
(___) . \   `         `\         |
 (__)-    ,/        (   |        |
      `--~|         |   |        |  Version : 1.0
          |         |   |		     |	Date :	11/03/2020

\**********************************************************************************************************************************************************************************************************************************/
#include "triangulation_lst.h"

// création du super-triangle qui "entoure" tous les points à trianguler
void super_triangle_lst(lst_vector_3d *points, lst_vector_i_triangle *triangles){
  point_3d p_max = point_min_lst(*points);
  point_3d p_min = point_max_lst(*points);
  double dx = p_max.x - p_min.x;
  double dy = p_max.y - p_min.y;
  double dmax = (dx > dy) ? dx : dy;
  double xmid = (p_max.x + p_min.x) / 2.0;
  double ymid = (p_max.y + p_min.y) / 2.0;

  point_3d p0 = point_3d_create(xmid - 20 * dmax, ymid - dmax, 0.0);
  point_3d p1 = point_3d_create(xmid, ymid + 20 * dmax, 0.0);
  point_3d p2 = point_3d_create(xmid + 20 * dmax, ymid - dmax, 0.0);

  lst_vector_3d_push(points, p2);
  lst_vector_3d_push(points, p1);
  lst_vector_3d_push(points, p0);

  i_triangle t = {0,1,2};
  lst_vector_i_triangle_push(triangles, t);
}

// calcul du triangle circonscrit propre à un triangle transmis en paramètre qui retourne le rayon au carré et le centre du cercle
bool is_inside_circum_circle_points_lst(point_3d p0,point_3d p1, point_3d p2, point_3d p3, point_3d *pc, double *rsqr, double epsilon){
    double fabs_y1y2 = fabs(p1.y-p2.y);
    double fabs_y2y3 = fabs(p2.y-p3.y);
    if (fabs_y1y2 < epsilon && fabs_y2y3 < epsilon)
        return(false);
    if (fabs_y1y2 < epsilon) {
        double m2 = - (p3.x - p2.x) / (p3.y-p2.y);
        double mx2 = (p2.x + p3.x) / 2.0;
        double my2 = (p2.y + p3.y) / 2.0;
        pc->x = (p2.x + p1.x) / 2.0;
        pc->y = m2 * (pc->x - mx2) + my2;
    } else if (fabs_y2y3 < epsilon) {
        double m1 = - (p2.x-p1.x) / (p2.y-p1.y);
        double mx1 = (p1.x + p2.x) / 2.0;
        double my1 = (p1.y + p2.y) / 2.0;
        pc->x = (p3.x + p2.x) / 2.0;
        pc->y = m1 * (pc->x - mx1) + my1;
    } else {
        double m1 = - (p2.x-p1.x) / (p2.y-p1.y);
        double m2 = - (p3.x-p2.x) / (p3.y-p2.y);
        double mx1 = (p1.x + p2.x) / 2.0;
        double mx2 = (p2.x + p3.x) / 2.0;
        double my1 = (p1.y + p2.y) / 2.0;
        double my2 = (p2.y + p3.y) / 2.0;
        pc->x = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        if (fabs_y1y2 > fabs_y2y3) {
            pc->y = m1 * (pc->x - mx1) + my1;
        } else {
            pc->y = m2 * (pc->x - mx2) + my2;
        }
    }
    double dx = p2.x - pc->x;
    double dy = p2.y - pc->y;
    *rsqr = dx*dx + dy*dy;
    dx = p0.x - pc->x;
    dy = p0.y - pc->y;
    double drsqr = dx*dx + dy*dy;
    return ((drsqr - *rsqr) <= epsilon);
}

// algorithme de bowyer-watson qui appel chaque fonctions présentes 
// dans cette librairie et retourne une liste de triangle "triangulés"
void bowyer_watson_lst(lst_vector_3d *points, lst_vector_i_triangle *triangles){
  super_triangle_lst(points, triangles);

  lst_vector_i_triangle mauvais_triangles;
  lst_vector_i_triangle_init(&mauvais_triangles);

  lst_vector_i_edge arretes;
  lst_vector_i_edge_init(&arretes);

  lst_vector_i_edge arretes_tmp;
  lst_vector_i_edge_init(&arretes_tmp);

  double rsqr = 0.0;
  point_3d pc = point_3d_create(0,0,0);
  double epsilon = 0.1;

  for (int i = points->length -1; i >= 3; i--){
    lst_vector_i_triangle_empty(&mauvais_triangles);
    for (int j = triangles->length-1; j >= 0; j--){
      i_triangle t;
      lst_vector_i_triangle_get(triangles, j, &t);

      point_3d p0;
      lst_vector_3d_get(points, i, &p0);
      point_3d p1;
      lst_vector_3d_get(points, t.p1, &p1);
      point_3d p2;
      lst_vector_3d_get(points, t.p2, &p2);
      point_3d p3;
      lst_vector_3d_get(points, t.p3, &p3);

      if(is_inside_circum_circle_points_lst(p0, p1, p2, p3, &pc, &rsqr, epsilon)){
        lst_vector_i_triangle_push(&mauvais_triangles, t);
      }
    }
    lst_vector_i_edge_empty(&arretes);
    manage_outer_edges_lst(&mauvais_triangles, &arretes, &arretes_tmp);
    remove_and_create_triangle_lst(&mauvais_triangles, triangles, &arretes, i);
  }
  clean_v_triangles_lst(points, triangles);
  lst_vector_i_triangle_free(&mauvais_triangles);
  lst_vector_i_edge_free(&arretes);
  lst_vector_i_edge_free(&arretes_tmp);
}

i_triangle form_triangle_from_edge_and_point_lst(i_edge a, int point){
  i_triangle t = {point,a.p1,a.p2};
  return t;
}

// compare les indices de deux triangles pour savoir si ce sont les memes
bool same_triangle_lst(i_triangle t1, i_triangle t2){
  return ((t1.p1 == t2.p1 || t1.p1 == t2.p2 || t1.p1 == t2.p3)
       && (t1.p2 == t2.p1 || t1.p2 == t2.p2 || t1.p2 == t2.p3)
       && (t1.p3 == t2.p1 || t1.p3 == t2.p2 || t1.p3 == t2.p3));
}

// regarde si une arrete appartient à un triangle
bool edge_common_with_triangle_lst(i_edge a, i_triangle t){
  return (((a.p1 == t.p1 || a.p1 == t.p2 || a.p1 == t.p3)
        && (a.p2 == t.p1 || a.p2 == t.p2 || a.p2 == t.p3)));
}

// donne la coordonnée x et y la plus petite d'une liste de point_3d (z pas utilisé)
point_3d point_min_lst(lst_vector_3d points){
  double x_min = points.head->data.x;
  double y_min = points.head->data.y;
  for (int i = 0; i < points.length; i++){
    point_3d p;
    lst_vector_3d_get(&points, i, &p);
    if(p.x < x_min){
        x_min = p.x;
    } if(p.y < y_min){
        y_min = p.y;
    }
  }
  return point_3d_create(x_min, y_min, 0.0);
}

// donne la coordonnée x et y la plus grande d'une liste de point_3d (z pas utilisé)
point_3d point_max_lst(lst_vector_3d points){
  double x_max = points.head->data.x;
  double y_max = points.head->data.y;
  for(int i = 0; i < points.length; i++){
    point_3d p;
    lst_vector_3d_get(&points, i, &p);
    if(p.x > x_max){
        x_max = p.x;
    } if(p.y > y_max){
        y_max = p.y;
    }
  }
  return point_3d_create(x_max, y_max, 0.0);
}

// algorithme de Bowyer-Watson : sous fonctions qui enlève le super triangle une fois la triangulation terminée
void clean_v_triangles_lst(lst_vector_3d* points, lst_vector_i_triangle* triangles){
  bool triangle_completly_clean = false;
  bool part_of_triangle_clean = false;
  // on retire tous les triangles composés d'une ou plusieurs arretes du super-triangle
  while (!triangle_completly_clean){
    part_of_triangle_clean = false;
    for (int i = triangles->length-1; i >= 0; i--){
      i_triangle t;
      lst_vector_i_triangle_get(triangles, i, &t);
      if (t.p1 == 0 || t.p1 == 1 || t.p1 == 2){
        lst_vector_i_triangle_remove(triangles, i);
        part_of_triangle_clean = true;
      }else if (t.p2 == 0 || t.p2 == 1 || t.p2 == 2){
        lst_vector_i_triangle_remove(triangles, i);
        part_of_triangle_clean = true;
      }else if (t.p3 == 0 || t.p3 == 1 || t.p3 == 2){
        lst_vector_i_triangle_remove(triangles, i);
        part_of_triangle_clean = true;
      }
      if(!part_of_triangle_clean && i == 0){
        triangle_completly_clean = true;
      }
    }
  }
  //remove les points du super-triangle
  for (int i = 0 ; i < 3; i++){
    point_3d p_tmp;
    lst_vector_3d_pop(points, &p_tmp);
  }
}

// algorithme de Bowyer-Watson : sous fonctions qui retire les triangles qui en apparence
// sont bon mais dont on est sûr qu'ils sont mauvais (grace au cercle circonscrit)
void remove_and_create_triangle_lst(lst_vector_i_triangle* mauvais_triangles, lst_vector_i_triangle* triangles, lst_vector_i_edge* arretes, int point){
  for (int j = mauvais_triangles->length-1; j >= 0; j--){
      for (int k = triangles->length-1; k >= 0; k--){
        i_triangle t1;
        lst_vector_i_triangle_get(mauvais_triangles, j, &t1);
        i_triangle t2;
        lst_vector_i_triangle_get(triangles, k, &t2);
        if(same_triangle_lst(t1, t2)){
          lst_vector_i_triangle_remove(triangles, k);
        }
      }
    }
    for (int j = 0; j < arretes->length; j++){
      i_edge e;
      lst_vector_i_edge_get(arretes, j, &e);
      i_triangle t = form_triangle_from_edge_and_point_lst(e, point);
      lst_vector_i_triangle_push(triangles, t);
    }
}

// algorithme de Bowyer-Watson : sous fonctions qui retires les arretes qui forment le trou que l'on doit supprimer 
// (arretes qui appartiennent à des mauvais triangles)
void manage_outer_edges_lst(lst_vector_i_triangle* mauvais_triangles, lst_vector_i_edge* arretes, lst_vector_i_edge* arretes_tmp){
  for (int j = mauvais_triangles->length-1; j >= 0; j--){
    lst_vector_i_edge_empty(arretes_tmp);
    i_triangle t;
    lst_vector_i_triangle_get(mauvais_triangles, j, &t);
    i_edge edge1 = i_edge_create(t.p1, t.p2);
    i_edge edge2 = i_edge_create(t.p1, t.p3);
    i_edge edge3 = i_edge_create(t.p2, t.p3);
    lst_vector_i_edge_push(arretes_tmp, edge1);
    lst_vector_i_edge_push(arretes_tmp, edge2);
    lst_vector_i_edge_push(arretes_tmp, edge3);
    for (int k = 0; k < 3; k++){
      bool conserver = true;
      for (int l = mauvais_triangles->length-1; l >= 0; l--){
        if(l != j){
          i_triangle t;
          i_edge e;
          lst_vector_i_edge_get(arretes_tmp, k, &e);
          lst_vector_i_triangle_get(mauvais_triangles, l, &t);
          if (edge_common_with_triangle_lst(e, t)){
            conserver = false;
            break;
          }
        }
      }
      if(conserver){
        i_edge e;
        lst_vector_i_edge_get(arretes_tmp, k, &e);
        lst_vector_i_edge_push(arretes, e);
      }
    }
  }
}
