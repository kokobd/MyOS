#include "gdt.h"
#include <stdio.h>

#pragma pack (push, 1)

struct Gdtr {
    // size of the GDT
    uint16_t limit;
    
    // base address of the GDT
    uint32_t base;
};

#pragma pack (pop)

#define MAX_DESCRIPTORS 16

static struct GdtDescriptor gdt[MAX_DESCRIPTORS] = {0};

static struct Gdtr gdtr;

static uint16_t gdtEntries = 0;

static void gdtInstall() {
    gdtr.limit = (sizeof(struct GdtDescriptor) * gdtEntries) - 1;
    gdtr.base = (uint32_t) &gdt[0];
    __asm__(
        "cli\n"
        "lgdt [eax]\n"
        : : "a"(&gdtr)
    );
}

static void gdtSetDescriptor(
        uint32_t index,
        uint32_t base,
        uint32_t limit,
        uint16_t flags,
        uint8_t dpl,
        uint8_t type) {
    if (index > MAX_DESCRIPTORS) {
        return;
    }

    gdt[index].baseLo = base & 0xFFFF;
    gdt[index].baseMid = (base >> 16) & 0xFF;
    gdt[index].baseHi = (base >> 24) & 0xFF;
    gdt[index].limit = limit & 0xFFFF;

    gdt[index].flags = flags | (dpl << 5) | type;
    if (index >= gdtEntries) {
        gdtEntries = index + 1;
    }
}

void gdtInitialize() {
    // null descriptor
    gdtSetDescriptor(0, 0, 0, 0, 0, 0);

    // default code descriptor
    gdtSetDescriptor(1, 0, 0xFFFFFFFF,
            GDT_FLAG_G | GDT_FLAG_DB | GDT_FLAG_P | GDT_FLAG_S,
            0,
            0x0A);

    // default data descriptor
    gdtSetDescriptor(2, 0, 0xFFFFFFFF,
            GDT_FLAG_G | GDT_FLAG_DB | GDT_FLAG_P | GDT_FLAG_S,
            0,
            0x02);

    gdtInstall();

    asm volatile (
        "cli\n"
        "mov ax, 0x10\n"
        "mov ds, ax\n"
        "mov ss, ax\n"
        "mov es, ax\n"
        "jmp 0x08:(.FixCS - 0x08048000 + 0x100000)\n"
        ".FixCS:\n"
        "nop"
    );
}