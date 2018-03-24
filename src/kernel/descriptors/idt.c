#include "idt.h"

#pragma pack (push, 1)

struct Idtr {
    // size of the IDT
    uint16_t limit;

    // base address of the IDT
    uint32_t base;
};

#pragma pack (pop)