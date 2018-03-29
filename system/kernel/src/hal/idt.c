#include "idt.h"
#include "asmutil.h"

#pragma pack (push, 1)

struct Idtr {
    // size of the IDT
    uint16_t limit;

    // base address of the IDT
    uint32_t base;
};

#pragma pack (pop)

static struct IdtDescriptor idt[256] = {0};

#define IDT_SIZE (sizeof(idt) / sizeof(struct IdtDescriptor))

static struct Idtr idtr;

static void idtInstall() {
    idtr.limit = sizeof(idt);
    idtr.base = (uint32_t) idt;
    __asm__(
        "lidt [eax]\n"
        : : "a"(&idtr)
    );
}

static void idtSetHandler(
        uint32_t i,
        uint8_t dpl,
        uint16_t sel,
        void (*handler)()
    ) {
    if (i >= IDT_SIZE
        || handler == 0)
        return;
    uint32_t handlerAddress = (uint32_t) handler;
    idt[i].baseLo = handlerAddress & 0x0000FFFF;
    idt[i].baseHi = (handlerAddress & 0xFFFF0000) >> 16;
    idt[i].reserved = 0;
    idt[i].sel = sel;
    idt[i].flags = ((dpl << 5) & 0x60) | 0x8E;
}

void defaultHandler() {
    // Do Nothing
    asm ( "iret" );
}

void idtInitialize(uint16_t sel) {
    for (uint32_t i = 0; i < IDT_SIZE; ++i) {
        idtSetHandler(i, 0, sel, defaultHandler);
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
