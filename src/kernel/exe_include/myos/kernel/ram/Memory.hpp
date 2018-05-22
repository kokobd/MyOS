#pragma once

#include <cstddef>
#include <cstdint>
#include <myos/kernel/ram/PageManager.hpp>
#include <myos/kernel/ram/Intel386PageTable.hpp>

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

private:
    void *kernelBegin;
    void *kernelEnd;

    PageManager pageManager;
};

}
