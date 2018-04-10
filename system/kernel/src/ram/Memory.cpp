#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/Kernel.hpp>

extern "C" int end;

namespace myos::kernel::ram {

Memory::Memory() {
    kernelBegin = reinterpret_cast<void *>(0x100000u);

    kernelBreak = reinterpret_cast<void *> (&end);

    kernelEnd = reinterpret_cast<void *>(0x200000u);
}

void *Memory::heapAllocate(size_t size) {

}

void Memory::heapDeallocate(void *pt) {
    // TODO free
}

}

using myos::kernel::Kernel;

void *operator new(size_t size) {
    return Kernel::getCurrentKernel().getMemory().heapAllocate(size);
}

void operator delete(void *pt) {
    Kernel::getCurrentKernel().getMemory().heapDeallocate(pt);
}

void *operator new[](size_t size) {
    return Kernel::getCurrentKernel().getMemory().heapAllocate(size);
}

void operator delete[](void *pt) {
    Kernel::getCurrentKernel().getMemory().heapDeallocate(pt);
}
