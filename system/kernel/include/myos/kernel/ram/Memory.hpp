#pragma once

#include <cstddef>
#include <cstdint>
namespace myos::kernel::ram {

class Memory {
public:
    Memory();

    void *heapAllocate(size_t size);

    void heapDeallocate(void *pt);

private:
    void *kernelBegin;
    void *kernelBreak; // Where the kernel heap ends
    void *kernelEnd;

    void kernelChangeBreak(intptr_t diff) {
        kernelBreak = reinterpret_cast<void *>(
                reinterpret_cast<uint8_t *>(kernelBreak) + diff
        );
    }
};

}
