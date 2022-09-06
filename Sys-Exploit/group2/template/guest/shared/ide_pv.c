#include <stdint.h>
#include "ide.h"
#include "hypercall.h"
#include "pmio.h"
#include <string.h>

#define STATUS_PORT 0x1F7
#define DATA_PORT   0x1F0

/**
 * Write a sector using paravirtualization.
 * @param sector_idx sector to write (0-indexed).
 * @param src address of the data to be written.
 */
void ide_write_sector_pv(int sector_idx, void *src){
    pv_disk* d = (pv_disk*) PV_ADDR;
    d->sector = sector_idx;
    memcpy((void*) d->data, src, SECTOR_SIZE);
    outb(0xABBA, DISK);
}
