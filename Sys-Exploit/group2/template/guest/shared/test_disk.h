#ifndef _TEST_DISK_H_
#define _TEST_DISK_H_

typedef void (*write_sector_func_t)(int sector_idx, void *src);

void test_disk(write_sector_func_t func);

#endif
