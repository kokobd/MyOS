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

    /**
     * @return virtual address of the first byte of user space
     */
    static uintptr_t userSpaceStart() {
        return 0x400000;
    }

    /**
     * @return virtual address of the last byte of user space.
     */
    static uintptr_t userSpaceEnd() {
        return 0x7FFFFF;
    }

private:
    void *kernelBegin;
    void *kernelEnd;

    PageManager pageManager;
};

}
