#pragma once

#include <stdint.h>

void idtInitialize();

/**
 * Set a handler in the IDT.
 * Note that handler implementations MUST use
 * 'returnFromInterruptHandler' to return.
 * @param i index into IDT
 * @param dpl privilege level
 * @param sel selector into GDT
 * @param handler the handler function
 */
void idtSetHandler(
        uint32_t i,
        uint8_t dpl,
        uint16_t sel,
        void (*handler)());

#define returnFromInterruptHandler(ret) \
do {\
    asm volatile (\
    "mov eax, %0\n"\
    "mov esp, ebp\n"\
    "pop ebp\n"\
    "iret\n"\
    : : "r" (ret)\
    : "eax", "esp"\
    );\
} while (0)
