#include <myos/kernel/SysCall.hpp>
#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/Kernel.hpp>

namespace myos::kernel {

SysCall::SysCall(Kernel &kernel)
        : kernel(kernel), handler(kernel) {
    kernel.getCPU().registerInterruptHandler(
            cpu::InterruptType::SYSTEM_CALL, &handler);
}

void SysCall::InterruptHandlerImpl::handleInterrupt(
        cpu::InterruptType interrupt,
        const cpu::RegisterState &registerState) {
    if (interrupt != cpu::InterruptType::SYSTEM_CALL) {
        return;
    }
    uint32_t ret = runSysCall(registerState.eax, registerState.ebx, registerState.ecx, registerState.edx);
    setReturnValue(ret);
}

uint32_t SysCall::InterruptHandlerImpl::runSysCall(
        uint32_t id,
        uint32_t arg1,
        uint32_t arg2,
        uint32_t arg3) {
    uint32_t ret = 0xFFFFFFFF;
    switch (id) {
        // TODO add system calls here
        default:
            break;
    }
    return ret;
}

SysCall::InterruptHandlerImpl::InterruptHandlerImpl(Kernel &kernel)
        : kernel(kernel) {}

}
