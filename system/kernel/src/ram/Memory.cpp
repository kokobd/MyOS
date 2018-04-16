#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/Kernel.hpp>
#include <myos/kernel/ram/VirtualMemoryMapping.hpp>

extern "C" int end;

namespace myos::kernel::ram {

Memory::Memory()
        : kernelHeap(&end) {
    kernelBegin = reinterpret_cast<void *>(0x100000u);
    kernelEnd = reinterpret_cast<void *>(0x200000u);

    identityMapping.install();
    VirtualMemoryMapping::enablePaging();
}

}

using myos::kernel::Kernel;

void *operator new(size_t size) {
    return Kernel::getCurrentKernel().getMemory().getKernelHeap().allocate(size);
}

void operator delete(void *pt) {
    Kernel::getCurrentKernel().getMemory().getKernelHeap().deallocate(pt);
}

void *operator new[](size_t size) {
    return Kernel::getCurrentKernel().getMemory().getKernelHeap().allocate(size);
}

void operator delete[](void *pt) {
    Kernel::getCurrentKernel().getMemory().getKernelHeap().deallocate(pt);
}
