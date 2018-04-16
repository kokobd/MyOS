#pragma once

#include <cstddef>
#include <cstdint>
#include "Heap.hpp"
#include "VirtualMemoryMapping.hpp"
namespace myos::kernel::ram {

/**
 * Manages memory for both kernel and user programs.
 * Kernel memory(0 to 0x1FFFFF) is pre-allocated.
 * User program memory should be allocated on demand,
 * using page frame as the unit.
 */
class Memory {
public:
    Memory();

    Heap &getKernelHeap() { return kernelHeap; }

private:
    void *kernelBegin;
    void *kernelEnd;
    Heap kernelHeap;

    VirtualMemoryMapping identityMapping;
};

}
