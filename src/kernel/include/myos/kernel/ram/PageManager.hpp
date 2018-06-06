#pragma once

#include <cstddef>
#include <myos/core/collections/BitSet.hpp>
#include <myos/core/collections/ArrayList.hpp>

namespace myos::kernel::ram {

/**
 * Manages page frames for user programs.
 * A PageManager simply records usage statistics of
 * page frames, it doesn't directly access them.
 */
class PageManager {
public:
    /**
     * Construct a PageFrameManager
     * @param start start address (physical) of all page frames. It must
     * be aligned to pageFrameSize.
     * @param pageSize size of each page
     * @param count (maximum) number of page frames
     */
    explicit PageManager(uintptr_t start, size_t pageSize, size_t count);

    /**
     * Allocate a page frame for use by user programs.
     * @return pointer to the beginning of a page frame,
     * nullptr if failed.
     */
    uintptr_t newPage();

    /**
     * Number of processes that are using this page frame.
     * @param physicalAddress the page frame to check
     * @return number of processes
     */
    uint32_t &processCount(uintptr_t physicalAddress);

    /**
     * Const version of 'processCount'
     */
    const uint32_t &processCount(uintptr_t physicalAddress) const;

    /**
     * Subtract the number of processes using a particular page
     * @param physicalAddress the page frame to deallocate.
     */
    void releasePage(uintptr_t physicalAddress);

private:
    // Each element is the number of processes sharing a page.
    core::collections::ArrayList<uint32_t> counters;

    uintptr_t start;

    /**
     * Convert from index of page frame to physical memory address.
     */
    uintptr_t indexToAddress(size_t index) const;

    size_t addressToIndex(uintptr_t address) const;

    const size_t PAGE_SIZE;
};

}
