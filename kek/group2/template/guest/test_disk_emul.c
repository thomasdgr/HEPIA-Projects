#include <stdint.h>
#include "pmio.h"
#include "test_disk.h"
#include "ide.h"

#define STATUS_PORT 0x1F7
#define DATA_PORT   0x1F0

// Purposedly incorrect code that's supposed to write a sector.
void write_sector_wrong1(int sector_idx, void *src) {
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	outb(0x1F2, 1);  // write 1 sector
	outb(0x1F3, sector_idx & 0xFF);  // send bits 0-7 of LBA
	outb(0x1F4, (sector_idx >> 8) & 0xFF);  // send bits 8-15 of LBA
	outb(0x1F5, (sector_idx >> 16) & 0xFF);  // send bits 16-23 of LBA
	outb(0x1F6, ((sector_idx >> 24) & 0x0F) | 0xE0);  // send bits 24-27 of LBA + set LBA mode

	outb(STATUS_PORT, 0x30);  // write with retry
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	uint16_t *data = (uint16_t *)src;
    // ERROR: missing one iteration!
	for (int i = 0; i < 120; i++) {   // write sector
		outw(DATA_PORT, *data);
		data++;
	}
}

// Purposedly incorrect code that's supposed to write a sector.
void write_sector_wrong2(int sector_idx, void *src) {
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	outb(0x1F2, 1);  // write 1 sector
	outb(0x1F3, sector_idx & 0xFF);  // send bits 0-7 of LBA
	outb(0x1F4, (sector_idx >> 8) & 0xFF);  // send bits 8-15 of LBA
	outb(0x1F5, (sector_idx >> 16) & 0xFF);  // send bits 16-23 of LBA
	outb(0x1F6, ((sector_idx >> 24) & 0x0F) | 0xE0);  // send bits 24-27 of LBA + set LBA mode

    // ERROR: writing wrong value!
	outb(STATUS_PORT, 0x60);  // write with retry
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	uint16_t *data = (uint16_t *)src;
	for (int i = 0; i < SECTOR_SIZE/2; i++) {   // write sector
		outw(DATA_PORT, *data);
		data++;
	}
}

// Purposedly incorrect code that's supposed to write a sector.
void write_sector_wrong3(int sector_idx, void *src) {
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	outb(0x1F2, 1);  // write 1 sector
	outb(0x1F3, sector_idx & 0xFF);  // send bits 0-7 of LBA
	outb(0x1F4, (sector_idx >> 8) & 0xFF);  // send bits 8-15 of LBA
	outb(0x1F5, (sector_idx >> 16) & 0xFF);  // send bits 16-23 of LBA
	outb(0x1F6, ((sector_idx >> 24) & 0x0F) | 0xE0);  // send bits 24-27 of LBA + set LBA mode

	outb(STATUS_PORT, 0x30);  // write with retry
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

    // ERROR: shouldn't write here!
    outb(0x50, 0);

	uint16_t *data = (uint16_t *)src;
	for (int i = 0; i < SECTOR_SIZE/2; i++) {   // write sector
		outw(DATA_PORT, *data);
		data++;
	}
}

// Purposedly incorrect code that's supposed to write a sector.
void write_sector_wrong4(int sector_idx, void *src) {
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

    // ERROR: writing to wrong port!
	outb(0x1F1, 1);  // write 1 sector
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

// Purposedly incorrect code that's supposed to write a sector.
void write_sector_wrong5(int sector_idx, void *src) {
	while((inb(STATUS_PORT) & 0xC0) != 0x40);  // wait for drive to be ready

	outb(0x1F2, 1);  // write 1 sector
	outb(0x1F3, sector_idx & 0xFF);  // send bits 0-7 of LBA
	outb(0x1F4, (sector_idx >> 8) & 0xFF);  // send bits 8-15 of LBA
	outb(0x1F5, (sector_idx >> 16) & 0xFF);  // send bits 16-23 of LBA
	outb(0x1F6, ((sector_idx >> 24) & 0x0F) | 0xE0);  // send bits 24-27 of LBA + set LBA mode

	outb(STATUS_PORT, 0x30);  // write with retry
    // ERROR: reading from wrong port!
	inb(DATA_PORT);

	uint16_t *data = (uint16_t *)src;
	for (int i = 0; i < SECTOR_SIZE/2; i++) {   // write sector
		outw(DATA_PORT, *data);
		data++;
	}
}

void guest_main() {
    test_disk(write_sector_wrong1);
    test_disk(write_sector_wrong2);
    test_disk(ide_write_sector_emul);
    test_disk(write_sector_wrong3);
    test_disk(write_sector_wrong4);
    test_disk(write_sector_wrong5);
}
