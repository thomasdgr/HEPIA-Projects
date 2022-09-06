#include <stdint.h>
#include "test_disk.h"
#include "ide.h"

void test_write_sect(write_sector_func_t func, int sector_index) {
    // Fill the sector with known values
    uint8_t sector[SECTOR_SIZE];
    for (int i = 0; i < SECTOR_SIZE; i++) {
        sector[i] = i % SECTOR_SIZE;
    }
    func(sector_index, sector);
}

//void test_disk(void (*write_sector)(int sector)) {
void test_disk(write_sector_func_t func) {
    test_write_sect(func, 307);
    test_write_sect(func, 71);
    test_write_sect(func, 511);
    test_write_sect(func, 17);
    test_write_sect(func, 147);
    test_write_sect(func, 31);
    test_write_sect(func, 219);
    test_write_sect(func, 0);
}
