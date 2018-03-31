#include <stdio.h>
#include "idt.h"
#include "asmutil.h"
#include "gdt.h"

#pragma pack (push, 1)

struct IdtDescriptor {
    // lower 16 bits of IR address
    uint16_t baseLo;

    // selector in GDT
    uint16_t sel;

    // reserved, should be 0
    uint8_t reserved;

    // bit flags
    // should be 1__01110 (for interrupt gate), where the underlines denotes the DPL
    uint8_t flags;

    // higher 16 bits of IR address
    uint16_t baseHi;
};

struct Idtr {
    // size of the IDT
    uint16_t limit;

    // base address of the IDT
    uint32_t base;
};

#pragma pack (pop)

#define IDT_LEN 256
#define IDT_SIZE (IDT_LEN * sizeof(struct IdtDescriptor))

static struct IdtDescriptor idt[IDT_LEN] = {0};

static struct Idtr idtr;

static void idtInstall() {
    idtr.limit = IDT_SIZE;
    idtr.base = (uint32_t) &idt[0];
    asm (
    "cli\n"
    "lidt [eax]\n"
    : : "a"(&idtr)
    );
}

void idtSetHandler(
        uint32_t i,
        uint8_t dpl,
        uint16_t sel,
        void (*handler)()) {
    if (i >= IDT_SIZE || handler == 0)
        return;
    uint32_t handlerAddress = (uint32_t) handler;
    idt[i].baseLo = (uint16_t) (handlerAddress & 0x0000FFFF);
    idt[i].baseHi = (uint16_t) ((handlerAddress >> 16) & 0xFFFF);
    idt[i].reserved = 0;
    idt[i].sel = sel;
    idt[i].flags = (dpl << 5) | (uint8_t) 0b10001110;
}

static void defaultHandler() {
    // Do Nothing
    returnFromInterruptHandler(0);
}

void idtInitialize() {
    for (uint32_t i = 0; i < IDT_LEN; ++i) {
        idtSetHandler(i, 0, 8, defaultHandler);
    }
    idtInstall();
}

// void issueInterrupt(int n) {
//     __asm__(
//         "mov byte ptr [" label_(genint) " + 1], al\n"
//         "jmp " label_(genint) "\n";
//         "genint:\n"
//         "int 0"
//         : : "a"(n)
//     );
// }
