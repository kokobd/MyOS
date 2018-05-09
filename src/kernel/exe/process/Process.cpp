#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/Kernel.hpp>
#include <cstring>

using myos::kernel::ram::Memory;
using myos::kernel::ram::VirtualMemoryMapping;

namespace myos::kernel::process {

Process::Process(const char *fileName) {
    setupStack();
}

void Process::setupStack() {
    Memory &memory = Kernel::getCurrentKernel().getMemory();

    // !!LOWER!! boundary of the stack.
    uint8_t *stackBasePhysical =
            static_cast<uint8_t *>(memory.allocatePageFrame());
    pageFrames.push(stackBasePhysical);
    virtualMemoryMapping.set(
            reinterpret_cast<void *>(0x800000u
                                     - VirtualMemoryMapping::pageFrameSize()),
            stackBasePhysical);
    registerState.esp = 0x7FFFFFu;
    registerState.ebp = registerState.esp;

}

void Process::switchVirtualMemory() {
    virtualMemoryMapping.install();
}

}
