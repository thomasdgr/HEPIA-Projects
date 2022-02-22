#ifndef LIDAR_H
#define LIDAR_H

#include "../vector/vector/vector.h"

typedef struct __attribute__((__packed__)) {
    char signature[4];
    uint16_t source_id;
    uint16_t global_encoding;
    uint32_t pid_data_1;
    uint16_t pid_data_2;
    uint16_t pid_data_3;
    uint8_t  pid_data_4[8];
    uint8_t version_major;
    uint8_t version_minor;
    char system_id[32];
    char gen_soft[32];
    uint16_t creation_day;
    uint16_t creation_year;
    uint16_t header_size;
    uint32_t off_to_point_data;
    uint32_t num_var_length_record;
    uint8_t point_data_format_id;
    uint16_t point_data_record_length;
    uint32_t num_point_records;
    uint32_t num_points_by_return[5];
    double x_scale_factor;
    double y_scale_factor;
    double z_scale_factor;
    double x_offset;
    double y_offset;
    double z_offset;
    double max_x;
    double min_x;
    double max_y;
    double min_y;
    double max_z;
    double min_z;
} header;

typedef struct __attribute__((__packed__)) {
    int32_t x, y, z;
    uint16_t intensity;
    uint8_t flags;
    unsigned char classification;
    unsigned char scan_angle_rank;
    unsigned char user_data;
    uint16_t point_source_id;
    double gps_time;
} point_record_1;

typedef struct {
    double x, y, z;
} point_3d;

header header_from_file(char *fname);
void print_header(header *h);
point_3d *points_from_file(char *fname, header h, uint32_t *num_points, bool is_print);
void print_point_record(point_record_1 *p);

#endif