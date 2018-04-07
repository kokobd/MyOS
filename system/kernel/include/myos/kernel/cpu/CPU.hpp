#pragma once

#include "GDT.hpp"
#include "IDT.hpp"
#include "InterruptHandler.hpp"

namespace myos::kernel::cpu {

class CPU {
public:
    CPU();

    void registerInterruptHandler(InterruptHandler &);

private:
    GDT<16> gdt;
    IDT idt;
};

}
