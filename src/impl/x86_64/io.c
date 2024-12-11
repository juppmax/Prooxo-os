#include <stdint.h>
#include "io.h"

uint8_t inb(uint16_t port) {
    uint8_t result;
    //inline asm to read a port 
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    //return result of reading the port
    return result;
}