#include "gdt.h"
#include "asmutil.h"

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

struct Gdtr {
    // size of the GDT
    uint16_t limit;

    // base address of the GDT
    uint32_t base;
};

#pragma pack (pop)

#define GDT_LEN 16
#define GDT_SIZE (GDT_LEN * sizeof(struct GdtDescriptor))

static struct GdtDescriptor gdt[GDT_LEN] = {0};

static struct Gdtr gdtr;

static uint16_t gdtEntries = 0;

static void gdtInstall() {
    gdtr.limit = GDT_SIZE;
    gdtr.base = (uint32_t) &gdt[0];
    asm (
    "lgdt [eax]\n"
    : : "a"(&gdtr)
    );
}

uint16_t gdtAddDescriptor(
        uint32_t base,
        uint32_t limit,
        uint16_t flags,
        uint8_t dpl,
        uint8_t type) {
    if (gdtEntries == GDT_LEN) {
        return 0xFFFF;
    }

    uint16_t i = gdtEntries++;
    gdt[i].baseLo = (uint16_t) (base & 0xFFFF);
    gdt[i].baseMid = (uint8_t) ((base >> 16) & 0xFF);
    gdt[i].baseHi = (uint8_t) ((base >> 24) & 0xFF);
    gdt[i].limit = (uint16_t) (limit & 0xFFFF);

    gdt[i].flags = flags | (dpl << 5) | type |
                   (uint16_t) ((limit >> 8) & 0xF00);
    return i << 3;
}

void gdtInitialize() {
    // null descriptor
    gdtAddDescriptor(0, 0, 0, 0, 0);

    // default code descriptor
    gdtAddDescriptor(0, 0xFFFFFFFF,
                     GDT_FLAG_G | GDT_FLAG_DB | GDT_FLAG_P | GDT_FLAG_S,
                     0,
                     0x0A);

    // default data descriptor
    gdtAddDescriptor(0, 0xFFFFFFFF,
                     GDT_FLAG_G | GDT_FLAG_DB | GDT_FLAG_P | GDT_FLAG_S,
                     0,
                     0x02);

    gdtInstall();

    asm volatile (
    "mov ax, 0x10\n"
    "mov ds, ax\n"
    "mov ss, ax\n"
    "mov es, ax\n"
    "jmp 0x08:" label_(.FixCS) "\n"
    ".FixCS:\n"
    "nop"
    );
}

uint16_t kernelCodeSelector() {
    return 0x8;
}
