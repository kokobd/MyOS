#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/cpu/InterruptHandler.hpp>
#include <myos/kernel/Kernel.hpp>

extern "C" void interruptHandlerPrim();

extern "C" int interruptHandlerPrimOffset;

extern "C" void cpu_init8259A();

namespace myos::kernel::cpu {

extern "C" uint32_t interruptDispatcher(uint32_t interrupt, uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx,
                                        uint32_t esi, uint32_t edi) {
    return CPU::getCurrentCPU().handleInterrupt(interrupt, RegisterState(eax, ebx, ecx, edx, esi, edi));
}

CPU::CPU() {
    cpu_init8259A();

    for (size_t i = 0; i < IDT::MAX_HANDLERS; ++i) {
        interruptHandlerRegistry[i] = &defaultHandler;
    }

    for (size_t i = 0; i < IDT::MAX_HANDLERS; ++i) {
        idt.setHandler(i, 0, GDT<16>::defaultCodeDescriptor(),
                       reinterpret_cast<void (*)()> (
                               (reinterpret_cast<uint8_t *>(interruptHandlerPrim))
                               + i * interruptHandlerPrimOffset));
    }

    enableHWInterrupts();
}

void CPU::enableHWInterrupts() {
    asm volatile (
    "sti\n"
    );
}

void CPU::disableHWInterrupts() {
    asm volatile (
    "cli\n"
    );
}

void CPU::registerInterruptHandler(InterruptType type, InterruptHandler *handler) {
    interruptHandlerRegistry[typeToNumber(type)] = handler;
}

CPU &CPU::getCurrentCPU() {
    Kernel::getCurrentKernel().getCPU();
}

uint32_t CPU::handleInterrupt(uint32_t interrupt, const RegisterState &registerState) {
    interruptHandlerRegistry[interrupt]->handleInterrupt(
            numberToType(static_cast<uint8_t>(interrupt)),
            registerState);
    return interruptHandlerRegistry[interrupt]->getReturnValue();
}

uint8_t CPU::typeToNumber(InterruptType type) {
    uint8_t number;
    switch (type) {
        case InterruptType::DIVISION_ERROR:
            number = 0x0;
            break;
        case InterruptType::GENERAL_PROTECTION_FAULT:
            number = 0xD;
            break;
        case InterruptType::PAGE_FAULT:
            number = 0xE;
            break;
        case InterruptType::TIMER:
            number = 0x20;
            break;
        case InterruptType::KEYBOARD:
            number = 0x21;
            break;
        case InterruptType::FLOPPY:
            number = 0x26;
            break;
        case InterruptType::SYSTEM_CALL:
            number = 0x80;
            break;
    }
    return number;
}

InterruptType CPU::numberToType(uint8_t number) {
    InterruptType type;
    switch (number) {
        case 0x0:
            type = InterruptType::DIVISION_ERROR;
            break;
        case 0xD:
            type = InterruptType::GENERAL_PROTECTION_FAULT;
            break;
        case 0xE:
            type = InterruptType::PAGE_FAULT;
            break;
        case 0x20:
            type = InterruptType::TIMER;
            break;
        case 0x21:
            type = InterruptType::KEYBOARD;
            break;
        case 0x26:
            type = InterruptType::FLOPPY;
            break;
        case 0x80:
            type = InterruptType::SYSTEM_CALL;
            break;
        default:
            type = InterruptType::GENERAL_PROTECTION_FAULT;
    }
    return type;
}

}
