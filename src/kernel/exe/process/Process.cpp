#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/Kernel.hpp>
#include <cstring>

using myos::kernel::ram::Memory;
using myos::kernel::ram::VirtualMemoryMapping;

namespace myos::kernel::process {

Process::Process(const char *fileName) {
}

void Process::switchVirtualMemory() {
    virtualMemoryMapping.install();
}

}
