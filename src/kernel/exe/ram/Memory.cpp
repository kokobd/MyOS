#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/Kernel.hpp>
#include <myos/kernel/ram/VirtualMemoryMapping.hpp>

extern "C" int end;

namespace myos::kernel::ram {

Memory::Memory()
        : pageFrameManager(reinterpret_cast<void *>(0x200000u), VirtualMemoryMapping::pageFrameSize(), 1536) {
    kernelBegin = reinterpret_cast<void *>(0x100000u);
    kernelEnd = reinterpret_cast<void *>(0x200000u);

    identityMapping.install();
    VirtualMemoryMapping::enablePaging();
}

void *Memory::allocatePageFrame() {
    return pageFrameManager.allocatePageFrame();
}

void Memory::deallocatePageFrame(void *pageFrame) {
    pageFrameManager.deallocatePageFrame(pageFrame);
}

}
