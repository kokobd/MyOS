#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/Kernel.hpp>
#include <myos/kernel/ram/Intel386PageTable.hpp>

extern "C" int end;

namespace myos::kernel::ram {

Memory::Memory()
        : pageManager(0x200000u, IPageTable<Intel386PageTable>::pageSize(), 1536) {
    kernelBegin = 0x100000u;
    kernelEnd = 0x200000u;
}

}
