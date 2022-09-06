#include <stdint.h>
#include "ide.h"
#include "pmio.h"

#define STATUS_PORT 0x1F7
#define DATA_PORT   0x1F0

/**
 * Write a sector.
 * @param sector_idx sector to write (0-indexed).
 * @param src address of the data to be written.
 */
void ide_write_sector_emul(int sector_idx, void *src) { 
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	outb(0x1F2, 1);  // write 1 sector
	outb(0x1F3, sector_idx & 0xFF);  // send bits 0-7 of LBA
	outb(0x1F4, (sector_idx >> 8) & 0xFF);  // send bits 8-15 of LBA
	outb(0x1F5, (sector_idx >> 16) & 0xFF);  // send bits 16-23 of LBA
	outb(0x1F6, ((sector_idx >> 24) & 0x0F) | 0xE0);  // send bits 24-27 of LBA + set LBA mode

	outb(STATUS_PORT, 0x30);  // write with retry
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	uint16_t *data = (uint16_t *)src;
	for (int i = 0; i < SECTOR_SIZE/2; i++) {   // write sector
		outw(DATA_PORT, *data);
		data++;
	}
}
