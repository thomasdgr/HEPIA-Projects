/**********************************************************************************************************************************************************************************************************************************\
			____
           /____ \               |  Projet : TP- Triangulation
           | _ _`\|              |  
    .-.   `| O O |               |  Auteur : Thomas Dagier
    | |   (- /_  -)              | 
    | |    |     |               |  Descripition : Fichier Lidar qui permet de lire un fichier.las, et stocker
 __/  |    | \__/|               |                 dans un tableau tous les points en 3D
(___) \.  _.\__. `\___           |
(___)  )\/  \_____/  ~\.         |
(___) . \   `         `\         |
 (__)-    ,/        (   |        |  
      `--~|         |   |        |  Version : 1.0
          |         |   |		 |	Date :	11/03/2020		
                                 
\**********************************************************************************************************************************************************************************************************************************/
#include "lidar.h"

// reécupérer l'entete d'un fichier .las (utile pour stocker le "offset_to_point_data" qui 
// permettera de sauter l'entete et de stocker les points)
header header_from_file(char *fname){
    FILE *f = fopen(fname, "rb");
    header entete;
    if(f){
        int nb_element = fread(&entete, sizeof(entete), 1, f);
        assert(nb_element>0);
        fclose(f);
    } else{
      printf("file %s doesn't exist\n",fname);
      exit(0);
    }
    return entete;
}

// vérifier les informations de l'entete
void print_header(header *h){
    printf("\n-- header lidar file --\n\n");
    printf(" signature : %s\n", h->signature);
    printf(" source_id : %u\n", h->source_id);
    printf(" global_encoding : %u\n", h->global_encoding);
    printf(" pid_data_1 : %u\n", h->pid_data_1);
    printf(" pid_data_2 : %u\n", h->pid_data_2);
    printf(" pid_data_3 : %u\n", h->pid_data_3);
    for(int i = 0; i < 8; i++){
        printf(" pid_data_4[%d] : %u\n", i, h->pid_data_4[i]);
    }
    printf(" version_major : %u\n", h->version_major);
    printf(" version_minor : %u\n", h->version_minor);
    printf(" system_id : %s\n", h->system_id);
    printf(" gen_soft : %s\n", h->gen_soft);
    printf(" creation_day : %u\n", h->creation_day);
    printf(" creation_year : %u\n", h->creation_year);
    printf(" header_size : %u\n", h->header_size);
    printf(" off_to_point_data : %u\n", h->off_to_point_data);
    printf(" num_var_length_record : %u\n", h->num_var_length_record);
    printf(" point_data_format_id : %u\n", h->point_data_format_id);
    printf(" point_data_record_length : %u\n", h->point_data_record_length);
    printf(" num_point_records : %u\n", h->num_point_records);
    for(int i = 0; i < 5; i++){
        printf(" num_points_by_return[%d] : %u\n", i, h->num_points_by_return[i]);
    }
    printf(" x_scale_factor : %f\n", h->x_scale_factor);
    printf(" y_scale_factor : %f\n", h->y_scale_factor);
    printf(" z_scale_factor : %f\n", h->z_scale_factor);
    printf(" x_offset : %f\n", h->x_offset);
    printf(" y_offset : %f\n", h->y_offset);
    printf(" z_offset : %f\n", h->z_offset);
    printf(" max_x : %f\n", h->max_x);
    printf(" min_x : %f\n", h->min_x);
    printf(" max_y : %f\n", h->max_y);
    printf(" min_y : %f\n", h->min_y);
    printf(" max_z : %f\n", h->max_z);
    printf(" min_z : %f\n", h->min_z);
    printf("\n-- end of header lidar file --\n");
}

// stocke tous les points_3d dans un tableau à partir de "offset_to_point_data"
point_3d *points_from_file(char *fname, header h, uint32_t *num_points, bool is_print){
    FILE *f = fopen(fname, "rb");
    point_record_1 p;
    *num_points = h.num_point_records;
    point_3d* points_array = calloc((*num_points), sizeof(point_3d));
    if(f){
        fseek(f, h.off_to_point_data, SEEK_SET);
        for(int i = 0; i < (int)(*num_points); i++){
            int value = fread(&p, sizeof(point_record_1), 1, f);
            assert(value>0);
            points_array[i].x = (p.x * h.x_scale_factor) +h.x_offset;
            points_array[i].y = (p.y * h.y_scale_factor) +h.y_offset;
            points_array[i].z = (p.z * h.z_scale_factor) +h.z_offset;
        } if(is_print){
            print_point_record(&p);
        }
        fclose(f);
    }
    return points_array;
}

// vérifier les informations de chaque point (appelé dans points_from_file si on le souhaite)
void print_point_record(point_record_1 *p){
    printf("\n-- header point element --\n\n");
    printf("x : %d\n", p->x);
    printf("y : %d\n", p->y);
    printf("z : %d\n", p->z);
    printf("intensity : %u\n", p->intensity);
    printf("flags : %u\n", p->flags);
    printf("classification : %u\n", p->classification);
    printf("scan_angle_rank : %u\n", p->scan_angle_rank);
    printf("user_data : %u\n", p->user_data);
    printf("point_source_id : %u\n", p->point_source_id);
    printf("gps_time : %f\n", p->gps_time);
    printf("\n-- end of header element --\n\n");
}
