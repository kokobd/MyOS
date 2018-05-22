#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/Kernel.hpp>

extern "C" int end;

namespace myos::kernel::ram {

Memory::Memory()
        : pageManager(reinterpret_cast<void *>(0x200000u), 1536) {
    kernelBegin = reinterpret_cast<void *>(0x100000u);
    kernelEnd = reinterpret_cast<void *>(0x200000u);
}

}
