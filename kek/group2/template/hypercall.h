#ifndef _HYPERCALL_H_
#define _HYPERCALL_H_

#define PV_ADDR 0xB9000
#define SECTOR_SIZE 512

#include <stdint.h>

// index of the hypercall to call
// TO ADD AN OTHER HYPERCALL, ADD HIS INDEX BELLOW
typedef enum {
	VGA = 0,
	DISK = 1,
} hypercall_t;

// the structure of the char sent by the guest paravirutalized
typedef struct _pv_vga_char{
    uint8_t ascii_char;  // the value of the char
    uint8_t bg_color;    // the color of the char's background
    uint8_t char_color;  // the color of the char
	uint8_t x,y;         // the coordinate of the char in the framebuffer shared with the host
} pv_vga_char;

// the structure of the content to write on the disk that are sent by the guest paravirutalized
typedef struct _pv_disk{
	int sector;					// the sector of the disk to write on
	uint8_t data[SECTOR_SIZE];  // the data to write
} pv_disk;

#endif
