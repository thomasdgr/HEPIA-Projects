#ifndef _DISK_VMM_H_
#define _DISK_VMM_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define NB_STATE 9
#define SECTOR_SIZE 512

uint8_t disk_machine_state_writing_from_guest(uint16_t pmio_port, uint16_t value, uint8_t nb_bytes);
uint8_t disk_machine_state_reading_from_guest(uint16_t pmio_port);
void disk_set_disk_ready();
void disk_set_disk_not_ready();
int disk_init(char* disk_file_name);
int disk_write(char sector_val[SECTOR_SIZE], uint32_t sector_idx);
int disk_free();

#endif


