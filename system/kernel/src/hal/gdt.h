#pragma once

#include <stdint.h>

/**
 * Initialize the GDT.
 * Put null descriptor, kernel code descriptor, kernel data descriptor
 * to 0, 1, 2, respectively.
 */
void gdtInitialize();

/**
 * Add a new descriptor to the GDT.
 * @param base base address
 * @param limit upper limit
 * @param flags should use the macros GDT_FLAG_*. Use bitwise or to combine them
 * @param dpl descriptor privilege level. Must be one of 0, 1, 2, 3
 * @param type type of the descriptor.
 * @return Selector of the newly added descriptor. 0xFFFFFFFF if the GDT is full.
 */
uint16_t gdtAddDescriptor(
        uint32_t base,
        uint32_t limit,
        uint16_t flags,
        uint8_t dpl,
        uint8_t type);

#define GDT_FLAG_G 0x8000
#define GDT_FLAG_DB 0x4000
#define GDT_FLAG_P 0x0080
#define GDT_FLAG_S 0x0010
