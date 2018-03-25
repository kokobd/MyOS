#ifndef KERNEL_DESCRIPTOR_GDT_H_
#define KERNEL_DESCRIPTOR_GDT_H_

#include <stdint.h>

#pragma pack (push, 1)

struct GdtDescriptor {
    // lower 16 bits of segment limit
    uint16_t limit;

    // lower 24 bits of base address
    uint16_t baseLo;
    uint8_t baseMid;

    uint16_t flags;

    // higher 8 bits of base address
    uint8_t baseHi;
};

#pragma pack (pop)

void gdtInitialize();

#define GDT_FLAG_G 0x8000
#define GDT_FLAG_DB 0x4000
#define GDT_FLAG_P 0x0080
#define GDT_FLAG_S 0x0100

#endif