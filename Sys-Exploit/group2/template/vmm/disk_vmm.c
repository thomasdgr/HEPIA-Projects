/**
* @file disk_vmm.c
* @brief disk management
*
* Manage disk usage with emulation and functions to open 
* and write on a disk
*
* @author Rod Quentin, Dagier Thomas
* @bug No known bugs.
* @date 02.04.2022
* @version 1.0
*/

#include "disk_vmm.h"

// the disk to write on
FILE* disk_file;
// the curent state of our state machine
uint8_t current_state = 0;
// data to send to the guest VM if he calls inb() depending on our state machine
uint32_t machine_state_disk[NB_STATE] = {0xFF, 0x40, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x40};
// the content to write on the disk
uint8_t sector_val[SECTOR_SIZE];
// flag to know if VMM is ready to write on disk 
bool vmm_disk_ready = false; 

/**
* state machine, part where we write from the guest to update state machine current state
* @param pmio_port the current port where data has been sent
* @param value the data that has been sent
* @param nb_bytes the number of byte that has been sent
* @return the data to send to the guest vm
*/
uint8_t disk_machine_state_writing_from_guest(uint16_t pmio_port, uint16_t value, uint8_t nb_bytes){
    static uint32_t sector_idx = 0;
    static uint32_t sector_mode = 0;
    static int count = 0;
    bool update_state = false;
    bool keep_state = false;
    switch(current_state){
        case 1:
            count = 0;
            sector_idx = 0;
            sector_mode = 0;
            update_state = (pmio_port == 0x1F2 && value == 1);
            break;
        case 2:
            update_state = (pmio_port == 0x1F3);
            sector_idx |= value;
            break;
        case 3:
            update_state = (pmio_port == 0x1F4);
            sector_idx |= value << 8;
            break;
        case 4:
            update_state = (pmio_port == 0x1F5);
            sector_idx |= value << 16;
            break;
        case 5:
            update_state = (pmio_port == 0x1F6);
            sector_idx |= (value << 24) & 0x0F;
            sector_mode |= (value << 24) & 0xF0;
            break;
        case 6:
            update_state = (pmio_port == 0x1F7 && value == 0x30);
            break;
        case 8:
            if(pmio_port == 0x1F0){
                if(nb_bytes == 2)
                    sector_val[count++] = value;
                sector_val[count++] = value >> 8;
                update_state = (count == SECTOR_SIZE);
                if(update_state)
                    disk_write((char*)sector_val, sector_idx);
                keep_state = true;
            }
            break;
    }
    if(update_state)
        current_state = (current_state + 1) % NB_STATE;
    else if(keep_state)
        current_state = current_state;
    else
        current_state = 0;
    return machine_state_disk[current_state];
}

/**
* state machine, part where we read from the guest to update state machine current state
* @param pmio_port the current port where data has been sent
* @return the data to send to the guest vm
*/
uint8_t disk_machine_state_reading_from_guest(uint16_t pmio_port){
    bool update_state = false;
    switch(current_state){
        case 0:
        case 7:
            update_state = (pmio_port == 0x1F7 && vmm_disk_ready);
            break;
    }
    current_state = update_state ? (current_state + 1) % NB_STATE : 0;
    return machine_state_disk[current_state];
}

/**
* set the flag to true so we are ready to write on disk
*/
void disk_set_disk_ready(){
    vmm_disk_ready = true;
}

/**
* set the flag to false so we are not ready to write on disk
*/
void disk_set_disk_not_ready(){
    vmm_disk_ready = false;
}

/**
* function used to open a given disk
* @param disk_file_name the name of the disk to open
* @return -1 on any error, else 0
*/
int disk_init(char * disk_file_name){
    disk_file = fopen(disk_file_name,"wb");
    if(disk_file == NULL)
        return -1;
    disk_set_disk_ready();
    return 0;
}

/**
* function used to write on a given disk
* @param disk_file_name the name of the disk to write on
* @return -1 on any error, else 0
*/
int disk_write(char sector_val[SECTOR_SIZE], uint32_t sector_idx){
    if(fseek(disk_file, sector_idx*SECTOR_SIZE, SEEK_SET) != 0)
        return -1;
    if(fwrite(sector_val , 1 ,SECTOR_SIZE , disk_file ) < SECTOR_SIZE)
        return -1;
    return 0;
}

/**
* function used to close a given disk
* @return -1 on any error, else 0
*/
int disk_free(){
    disk_set_disk_not_ready();
    if(fclose(disk_file) == EOF)
        return -1;
    return 0;
}