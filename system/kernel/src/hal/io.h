#pragma once

#include <stdint.h>

inline static uint8_t inb(uint32_t port) {
    uint8_t data = 0;
    asm volatile(
    "in %0, dx"
    : "=r" (data)
    : "d" (port)
    );
    return data;
}

inline static void outb(uint32_t port, uint8_t data) {
    asm volatile(
    "out dx, al"
    : : "d" (port), "a" (data)
    );
}
