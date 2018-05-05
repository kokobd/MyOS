#pragma once

#include "IDT.hpp"
#include "InterryptType.hpp"
#include "RegisterState.hpp"

namespace myos::kernel::cpu {

class InterruptHandler;

class CPU {
public:
    CPU();

    void registerInterruptHandler(InterruptType type, InterruptHandler *handler);

    static CPU &getCurrentCPU();

    void handleInterrupt(uint32_t interrupt, RegisterState &registerState);

    void enterUserCode(void *target, void *userStack);

private:
    IDT idt;

    InterruptHandler *interruptHandlerRegistry[IDT::MAX_HANDLERS];

    uint8_t static typeToNumber(InterruptType type);

    InterruptType static numberToType(uint8_t number);
};

}
