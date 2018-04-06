#pragma once

#include <cstdint>
#include <cstddef>

namespace myos::kernel::cpu {

template<size_t MAX_DESCRIPTORS>
class GDT {
public:
    /**
     * The constructor will create 3 default descriptors,
     * and install the GDT to CPU.
     * Additional descriptors may be added by calling
     * 'addDescriptor' method.
     */
    GDT() : entries(0) {
        addDescriptor(0, 0, 0, 0, 0);

        // default code descriptor
        addDescriptor(0, 0xFFFFFFFF,
                      FLAG_G | FLAG_DB | FLAG_P | FLAG_S,
                      0,
                      0x0A);

        // default data descriptor
        addDescriptor(0, 0xFFFFFFFF,
                      FLAG_G | FLAG_DB | FLAG_P | FLAG_S,
                      0,
                      0x02);

        installToCPU();

        asm volatile (
        "xor eax, eax\n"
        "mov ax, 0x10\n"
        "mov ds, ax\n"
        "mov ss, ax\n"
        "mov es, ax\n"
        "jmp 0x08:.FixCS\n"
        ".FixCS:\n"
        "nop"
        );
    }

    ~GDT() = default;

    using Selector = uint16_t;

    /**
     * Add a new descriptor to the GDT.
     * @param base base address
     * @param limit upper limit
     * @param flags should use the macros GDT_FLAG_*. Use bitwise or to combine them
     * @param dpl descriptor privilege level. Must be one of 0, 1, 2, 3
     * @param type type of the descriptor.
     * @return Selector of the newly added descriptor. 0xFFFFFFFF if the GDT is full.
     */
    Selector addDescriptor(
            uint32_t base,
            uint32_t limit,
            uint16_t flags,
            uint8_t dpl,
            uint8_t type) {
        if (entries == MAX_DESCRIPTORS) {
            return 0xFFFF;
        }

        size_t i = entries++;
        gdt[i].baseLo = (uint16_t) (base & 0xFFFF);
        gdt[i].baseMid = (uint8_t) ((base >> 16) & 0xFF);
        gdt[i].baseHi = (uint8_t) ((base >> 24) & 0xFF);
        gdt[i].limit = (uint16_t) (limit & 0xFFFF);

        gdt[i].flags = flags | (dpl << 5) | type |
                       (uint16_t) ((limit >> 8) & 0xF00);

        return static_cast<Selector>(i << 3);
    }

    static Selector defaultCodeDescriptor() {
        return 0x08;
    }

    static Selector defaultDataDescriptor() {
        return 0x10;
    }

private:
    void installToCPU() {
        gdtr.limit = sizeof(Descriptor) * MAX_DESCRIPTORS;
        gdtr.base = reinterpret_cast<uint32_t>(&gdt[0]);
        asm (
        "lgdt [eax]\n"
        : : "a"(&gdtr)
        );
    }

#pragma pack (push, 1)

    struct Descriptor {
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

    Descriptor gdt[MAX_DESCRIPTORS];

    Gdtr gdtr;

    size_t entries;

public:
    static const uint16_t FLAG_G = 0x8000;
    static const uint16_t FLAG_DB = 0x4000;
    static const uint16_t FLAG_P = 0x0080;
    static const uint16_t FLAG_S = 0x0010;
};

}
