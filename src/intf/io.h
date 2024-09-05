#pragma once

#include <stdint.h>

#ifndef __bool_true_false_are_defined
#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined 1
#endif

// Memory Access Functions

// Read a 32-bit value from a far pointer (selector + offset)
static inline uint32_t farpeekl(uint16_t sel, void* off);

// Write an 8-bit value to a far pointer (selector + offset)
static inline void farpokeb(uint16_t sel, void* off, uint8_t v);

// I/O Access Functions

// Send an 8-bit value to an I/O port
static inline void outb(uint16_t port, uint8_t val);

// Receive an 8-bit value from an I/O port
static inline uint8_t inb(uint16_t port);

// Wait for a very short time (1-4 microseconds)
static inline void io_wait(void);

// Interrupt-related Functions

// Check if interrupts are enabled
static inline bool are_interrupts_enabled();

// Load a new Interrupt Descriptor Table (IDT)
static inline void lidt(void* base, uint16_t size);

// CPU-related Functions

// Get CPU identification
static inline void cpuid(int code, uint32_t* a, uint32_t* d);

// Read the current value of the CPU's time-stamp counter
static inline uint64_t rdtsc(void);

// Read the value in a control register (CR0)
static inline unsigned long read_cr0(void);

// Invalidate a TLB entry for a specific virtual address
static inline void invlpg(void* m);

// Write a 64-bit value to a Model-Specific Register (MSR)
static inline void wrmsr(uint64_t msr, uint64_t value);

// Read a 64-bit value from a Model-Specific Register (MSR)
static inline uint64_t rdmsr(uint64_t msr);