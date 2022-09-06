#ifndef _PMIO_H_
#define _PMIO_H_

#include <stdint.h>

// Write a 8-bit value to the specified port
extern void outb(uint16_t port, uint8_t data);
// Read a 8-bit value from the specified port
extern uint8_t inb(uint16_t port);

// Write a 16-bit value to the specified port
extern void outw(uint16_t port, uint16_t data);
// Read a 16-bit value from the specified port
extern uint16_t inw(uint16_t port);

// Write a 32-bit value to the specified port
extern void outd(uint16_t port, uint32_t data);
// Read a 32-bit value from the specified port
extern uint32_t ind(uint16_t port);

#endif
