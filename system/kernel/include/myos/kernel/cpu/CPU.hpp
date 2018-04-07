#pragma once

#include "GDT.hpp"
#include "IDT.hpp"
#include "InterruptHandler.hpp"
#include "RegisterState.hpp"

namespace myos::kernel::cpu {

class CPU {
public:
    CPU();

    void registerInterruptHandler(InterruptHandler *handler);

    void enableHWInterrupts();

    void disableHWInterrupts();

    static CPU &getCurrentCPU();

    uint32_t handleInterrupt(uint32_t interrupt, const RegisterState &registerState);

private:
    GDT<16> gdt;
    IDT idt;

    InterruptHandler *interruptHandlerRegistry[IDT::MAX_HANDLERS];
};

}
