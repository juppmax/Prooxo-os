#include "io.h"
#include <stdint.h>

#ifndef __bool_true_false_are_defined
#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined 1
#endif


//Memory acess
//read 8/16/32-bit values
static inline uint32_t farpeekl(uint16_t sel, void* off){
    uint32_t ret;
    asm ( "push %%fs\n\t"
          "mov  %1, %%fs\n\t"
          "mov  %%fs:(%2), %0\n\t"
          "pop  %%fs"
          : "=r"(ret) : "g"(sel), "r"(off) );
    return ret;
}
//write 8/16/32-bit values 
static inline void farpokeb(uint16_t sel, void* off, uint8_t v){
    asm ( "push %%fs\n\t"
          "mov  %0, %%fs\n\t"
          "movb %2, %%fs:(%1)\n\t"
          "pop %%fs"
          : : "g"(sel), "r"(off), "r"(v) );
    /* TODO: Should "memory" be in the clobber list here? */
}

//I/O acess
//Send a 8/16/32-bit value to a I/O location 
static inline void outb(uint16_t port, uint8_t val){
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}
//Receive a 8/16/32-bit value from an I/O location
static inline uint8_t inb(uint16_t port){
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}
//wait for a very small amount of time (1-4 icroseconds)
static inline void io_wait(void){
    outb(0x80, 0);
}

//Interrupt related functions
static inline bool are_interrupts_enabled(){
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

//Define a new interrupt table 
static inline void lidt(void* base, uint16_t size){
    // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        void*    base;
    } __attribute__((packed)) IDTR = { size, base };

    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

//CPU related functions
//Get CPU identification
static inline void cpuid(int code, uint32_t* a, uint32_t* d){
    asm volatile ( "cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx" );
}

//Read the current value of the CPU's time-stamp counter and store into EDX:EAX
static inline uint64_t rdtsc(){
    uint64_t ret;
    asm volatile ( "rdtsc" : "=A"(ret) );
    return ret;
}

//TO-DO Read the value in a control register.