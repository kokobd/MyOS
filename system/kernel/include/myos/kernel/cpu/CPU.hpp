#pragma once

#include "GDT.hpp"
#include "IDT.hpp"
#include "InterruptHandler.hpp"
#include "NoopHandler.hpp"
#include "InterryptType.hpp"
#include "RegisterState.hpp"

namespace myos::kernel::cpu {

class CPU {
public:
    CPU();

    void registerInterruptHandler(InterruptType type, InterruptHandler *handler);

    void enableHWInterrupts();

    void disableHWInterrupts();

    static CPU &getCurrentCPU();

    uint32_t handleInterrupt(uint32_t interrupt, const RegisterState &registerState);

private:
    GDT<16> gdt;
    IDT idt;

    InterruptHandler *interruptHandlerRegistry[IDT::MAX_HANDLERS];
    NoopHandler defaultHandler;

    uint8_t static typeToNumber(InterruptType type);

    InterruptType static numberToType(uint8_t number);
};

}
