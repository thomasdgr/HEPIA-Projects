#include "test_disk.h"
#include "ide.h"

void guest_main() {
    test_disk(ide_write_sector_pv);
}
