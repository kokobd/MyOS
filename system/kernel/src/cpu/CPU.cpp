#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/cpu/InterruptHandler.hpp>
#include <myos/kernel/Kernel.hpp>

extern "C" void interruptHandlerPrim();

extern "C" int interruptHandlerPrimOffset;

namespace myos::kernel::cpu {

extern "C" uint32_t interruptDispatcher(uint32_t interrupt, uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx,
                                        uint32_t esi, uint32_t edi) {
    return CPU::getCurrentCPU().handleInterrupt(interrupt, RegisterState(eax, ebx, ecx, edx, esi, edi));
}

CPU::CPU() {
    for (size_t i = 0; i < IDT::MAX_HANDLERS; ++i) {
        interruptHandlerRegistry[i] = nullptr;
    }

    for (size_t i = 0; i < IDT::MAX_HANDLERS; ++i) {
        idt.setHandler(i, 0, GDT<16>::defaultCodeDescriptor(),
                       reinterpret_cast<void (*)()> (
                               (reinterpret_cast<uint8_t *>(interruptHandlerPrim))
                               + i * interruptHandlerPrimOffset));
    }
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

void CPU::registerInterruptHandler(InterruptHandler *handler) {
    interruptHandlerRegistry[handler->getInterruptNumber()] = handler;
}

CPU &CPU::getCurrentCPU() {
    Kernel::getCurrentKernel().getCPU();
}

uint32_t CPU::handleInterrupt(uint32_t interrupt, const RegisterState &registerState) {
    interruptHandlerRegistry[interrupt]->handleInterrupt(registerState);
    return interruptHandlerRegistry[interrupt]->getReturnValue();
}

}
