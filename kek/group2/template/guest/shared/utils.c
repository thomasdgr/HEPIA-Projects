#include "utils.h"

void memset(void *dst, uint8_t value, u_int count) {
	uint8_t *d = dst;
	while (count--) {
		*d++ = value;
    }
}
