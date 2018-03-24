#ifndef KERNEL_DESCRIPTOR_IDT_H_
#define KERNEL_DESCRIPTOR_IDT_H_

#include <stdint.h>

#pragma pack (push, 1)

struct IdtDescriptor {
    // lower 16 bits of IR address
    uint16_t baseLo;

    // selector in GDT
    uint16_t sel;

    // reserved, should be 0
    uint8_t reserved;

    // bit flags
    uint8_t flags;

    // higher 16 bits of IR address
    uint16_t baseHi;
};

#pragma pack (pop)

#endif
