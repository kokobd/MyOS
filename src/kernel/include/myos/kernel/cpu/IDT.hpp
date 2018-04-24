#pragma once

#include <cstdint>
#include <cstddef>

namespace myos::kernel::cpu {

class IDT {
public:
    IDT();

    void setHandler(uint8_t index, uint8_t dpl, uint16_t selectorInGDT,
                    void (*handler)());

    static constexpr size_t MAX_HANDLERS = 256;

private:
#pragma pack (push, 1)
    struct Descriptor {
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

private:

    Descriptor idt[MAX_HANDLERS];
    Idtr idtr;

    void install();
};

}
