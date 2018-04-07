#include <myos/kernel/cpu/IDT.hpp>
#include <myos/kernel/cpu/GDT.hpp>
#include <cstddef>

namespace myos::kernel::cpu {

IDT::IDT() {
    idtr.limit = MAX_HANDLERS * sizeof(Descriptor);
    idtr.base = (uint32_t) &idt[0];

    install();
}

void IDT::setHandler(uint8_t index, uint8_t dpl, uint16_t selectorInGDT,
                     void (*handler)()) {
    if (index >= MAX_HANDLERS || handler == nullptr)
        return;
    uint32_t handlerAddress = (uint32_t) handler;
    idt[index].baseLo = (uint16_t) (handlerAddress & 0x0000FFFF);
    idt[index].baseHi = (uint16_t) ((handlerAddress >> 16) & 0xFFFF);
    idt[index].reserved = 0;
    idt[index].sel = selectorInGDT;
    idt[index].flags = (dpl << 5) | (uint8_t) 0b10001110;
}

void IDT::install() {
    asm volatile (
    "cli\n"
    "lidt [eax]\n"
    : : "a"(&idtr)
    );
}

}