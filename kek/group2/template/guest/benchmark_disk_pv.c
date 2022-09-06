#include <stdint.h>
#include "pmio.h"
#include "ide.h"
#include <time.h>
#include <stdio.h>

typedef void (*write_sector_func_t)(int sector_idx, void *src);

void test_benchmark(write_sector_func_t func, int sector_index) {
    uint8_t sector[SECTOR_SIZE];
    for (int i = 0; i < SECTOR_SIZE; i++) {
        sector[i] = i % SECTOR_SIZE;
    }
    func(sector_index, sector);
}

void guest_main(){
    int k = 1000;
    for(int i = 0; i < k; i++){
        test_benchmark(ide_write_sector_pv, i);
    }
}