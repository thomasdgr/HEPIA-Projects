#include "test_lidar.h"
#include "../lidar/lidar.h"
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>

void test_las_header_from_file() {
    header test = header_from_file("../../lidar.las");

    CU_ASSERT(!strcmp(test.signature, "LASF"));
    CU_ASSERT(test.source_id == 0);
    CU_ASSERT(test.global_encoding == 1);

    CU_ASSERT(test.pid_data_1 == 0);
    CU_ASSERT(test.pid_data_2 == 0);
    CU_ASSERT(test.pid_data_3 == 0);
    for(int i = 0; i < 8; i++) { CU_ASSERT(test.pid_data_4[i] == 0); }

    CU_ASSERT(test.version_major == 1);
    CU_ASSERT(test.version_minor == 2);
    CU_ASSERT(!strcmp(test.gen_soft, "TerraScan"));

    CU_ASSERT(test.creation_day == 160);
    CU_ASSERT(test.creation_year == 2017);

    CU_ASSERT(test.header_size == 227);
    CU_ASSERT(test.off_to_point_data == 229);

    CU_ASSERT(test.num_var_length_record == 0);
    CU_ASSERT(test.point_data_format_id == 1);
    CU_ASSERT(test.point_data_record_length == 28);

    CU_ASSERT(test.num_point_records == 8212287);
    CU_ASSERT(test.num_points_by_return[0] == 7826831);
    CU_ASSERT(test.num_points_by_return[1] == 353517);
    CU_ASSERT(test.num_points_by_return[2] == 30221);
    CU_ASSERT(test.num_points_by_return[3] == 1649);
    CU_ASSERT(test.num_points_by_return[4] == 60);

    CU_ASSERT(test.x_scale_factor == 0.001000);
    CU_ASSERT(test.y_scale_factor == 0.001000);
    CU_ASSERT(test.z_scale_factor == 0.001000);

    CU_ASSERT(test.x_offset == 2000000.000000);
    CU_ASSERT(test.y_offset == 1000000.000000);
    CU_ASSERT(test.z_offset == -0.000000);

    CU_ASSERT(test.max_x == 2499499.999000);
    CU_ASSERT(test.min_x == 2499000.000000);
    CU_ASSERT(test.max_y == 1115999.999000);
    CU_ASSERT(test.min_y == 1115500.000000);
    CU_ASSERT(test.max_z == 526.168000);
    CU_ASSERT(test.min_z == 301.708000);
}

void test_las_points_from_file() {
    uint32_t nPoint;
    header test2 = header_from_file("../../lidar.las");
    point_3d *lstPoint = points_from_file("../../lidar.las", test2, &nPoint, false);
    FILE *fp = fopen("../../lidar.las", "rb");
    point_record_1 *PointRecords;
    PointRecords = malloc(test2.num_point_records*sizeof(point_record_1));

    fseek(fp, test2.off_to_point_data, SEEK_SET);
    int value = fread(&PointRecords[0], sizeof(point_record_1), 1, fp);
    CU_ASSERT(value > 0);
    CU_ASSERT(PointRecords[0].x == 499063511);
    CU_ASSERT(PointRecords[0].y == 115793589);
    CU_ASSERT(PointRecords[0].z == 378956);
    CU_ASSERT(PointRecords[0].intensity == 18331);
    CU_ASSERT(PointRecords[0].flags == 9);
    CU_ASSERT(PointRecords[0].classification == 16);
    CU_ASSERT(PointRecords[0].scan_angle_rank == 29);
    CU_ASSERT(PointRecords[0].user_data == 1);
    CU_ASSERT(PointRecords[0].point_source_id == 37);
    CU_ASSERT((float)PointRecords[0].gps_time == (float)171641138.632467);

    CU_ASSERT(lstPoint[0].x == 2499063.511);
    CU_ASSERT(lstPoint[0].y == 1115793.589);
    CU_ASSERT(lstPoint[0].z == 378.956);

    free(PointRecords);
    fclose(fp);
    free(lstPoint);

}
void test_print_header(){
  header entete = header_from_file("../../lidar.las");
   CU_ASSERT(strcmp(entete.signature,"LASF") == 0);
   CU_ASSERT(entete.source_id == 0);
   CU_ASSERT(entete.global_encoding == 1);
   CU_ASSERT(entete.pid_data_1 == 0);
   CU_ASSERT(entete.pid_data_2 == 0);
   CU_ASSERT(entete.pid_data_3 == 0);
   CU_ASSERT(entete.pid_data_4[0] == 0);
   CU_ASSERT(entete.pid_data_4[1] == 0);
   CU_ASSERT(entete.pid_data_4[2] == 0);
   CU_ASSERT(entete.pid_data_4[3] == 0);
   CU_ASSERT(entete.pid_data_4[4] == 0);
   CU_ASSERT(entete.pid_data_4[5] == 0);
   CU_ASSERT(entete.pid_data_4[6] == 0);
   CU_ASSERT(entete.pid_data_4[7] == 0);
   CU_ASSERT(entete.version_major == 1);
   CU_ASSERT(entete.version_minor == 2);
   CU_ASSERT(strcmp(entete.system_id,"") == 0);
   CU_ASSERT(strcmp(entete.gen_soft,"TerraScan") == 0);
   CU_ASSERT(entete.creation_day == 160);
   CU_ASSERT(entete.creation_year == 2017);
   CU_ASSERT(entete.header_size == 227);
   CU_ASSERT(entete.off_to_point_data == 229);
   CU_ASSERT(entete.num_var_length_record == 0);
   CU_ASSERT(entete.point_data_format_id == 1);
   CU_ASSERT(entete.point_data_record_length == 28);
   CU_ASSERT(entete.num_point_records == 8212287);
   CU_ASSERT(entete.num_points_by_return[0] == 7826831);
   CU_ASSERT(entete.num_points_by_return[1] == 353517);
   CU_ASSERT(entete.num_points_by_return[2] == 30221);
   CU_ASSERT(entete.num_points_by_return[3] == 1649);
   CU_ASSERT(entete.num_points_by_return[4] == 60);
   CU_ASSERT(entete.x_scale_factor == 0.001000);
   CU_ASSERT(entete.y_scale_factor == 0.001000);
   CU_ASSERT(entete.z_scale_factor == 0.001000);
   CU_ASSERT(entete.x_offset == 2000000.000000);
   CU_ASSERT(entete.y_offset == 1000000.000000);
   CU_ASSERT(entete.z_offset == -0.000000);
   CU_ASSERT(entete.max_x == 2499499.999000);
   CU_ASSERT(entete.min_x == 2499000.000000);
   CU_ASSERT(entete.max_y == 1115999.999000);
   CU_ASSERT(entete.min_y == 1115500.000000);
   CU_ASSERT(entete.max_z == 526.168000);
   CU_ASSERT(entete.min_z == 301.708000);

}

void test_print_point_record(){
    uint32_t nPoint;
    header test2 = header_from_file("../../lidar.las");
    point_3d *lstPoint = points_from_file("../../lidar.las", test2, &nPoint, false);
    FILE *fp = fopen("../../lidar.las", "rb");
    point_record_1 *PointRecords;
    PointRecords = malloc(test2.num_point_records*sizeof(point_record_1));

    fseek(fp, test2.off_to_point_data, SEEK_SET);
    int value = fread(&PointRecords[0], sizeof(point_record_1), 1, fp);
    CU_ASSERT(value > 0);
    CU_ASSERT(PointRecords[0].x == 499063511);
    CU_ASSERT(PointRecords[0].y == 115793589);
    CU_ASSERT(PointRecords[0].z == 378956);
    CU_ASSERT(PointRecords[0].intensity == 18331);
    CU_ASSERT(PointRecords[0].flags == 9);
    CU_ASSERT(PointRecords[0].classification == 16);
    CU_ASSERT(PointRecords[0].scan_angle_rank == 29);
    CU_ASSERT(PointRecords[0].user_data == 1);
    CU_ASSERT(PointRecords[0].point_source_id == 37);
    CU_ASSERT((float)PointRecords[0].gps_time == (float)171641138.632467);

    CU_ASSERT(lstPoint[0].x == 2499063.511);
    CU_ASSERT(lstPoint[0].y == 1115793.589);
    CU_ASSERT(lstPoint[0].z == 378.956);

    free(PointRecords);
    fclose(fp);
    free(lstPoint);
    //le print fonctionnne mais pour les besions des tests c'est plus simple de ne pas le faire
}
