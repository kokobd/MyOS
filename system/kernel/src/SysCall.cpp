#include <myos/kernel/SysCall.hpp>
#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/Kernel.hpp>
#include "shell.h"
#include "filesystem/file.h"

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
        case 0:
            ret = static_cast<uint32_t>(kernel_filesystem_file_fopen((const char *) arg1, (uint32_t) arg2));
            break;
        case 1:
            ret = static_cast<uint32_t>(kernel_filesystem_file_fclose(arg1));
            break;
        case 2:
            ret = static_cast<uint32_t>(kernel_filesystem_file_fread(arg1, (uint8_t *) arg2, (size_t) arg3));
            break;
        case 3:
            kernel_shell_termPutChar(kernel_shell_getGlobalTerminal(), (char) arg1);
            ret = 0;
            break;
        case 4:
            ret = static_cast<uint32_t>(kernel_shell_termGetChar(kernel_shell_getGlobalTerminal()));
            break;
        case 5:
            ret = kernel_filesystem_file_fGetSize(arg1);
            break;
        case 6:
            ret = static_cast<uint32_t>((int32_t) kernel_shell_getGlobalTerminal()->arg);
        default:
            break;
    }
    return ret;
}

SysCall::InterruptHandlerImpl::InterruptHandlerImpl(Kernel &kernel)
        : kernel(kernel) {}

}
