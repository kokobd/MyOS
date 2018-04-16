#pragma once

#include <cstddef>
#include <myos/kernel/common/BitSet.hpp>

namespace myos::kernel::ram {

/**
 * Manages page frames for user programs.
 * A PageFrameManager merely records usage statistics about
 * page frames, it doesn't directly access them.
 */
class PageFrameManager {
public:
    /**
     * Construct a PageFrameManager
     * @param start start address (physical) of all page frames. It must
     * be aligned to pageFrameSize.
     * @param pageFrameSize size of each page frame
     * @param count (maximum) number of page frames
     */
    explicit PageFrameManager(void *start, size_t pageFrameSize, size_t count);

    /**
     * Allocate a page frame for use by user programs.
     * @return pointer to the beginning of a page frame,
     * nullptr if failed.
     */
    void *allocatePageFrame();

    /**
     * Deallocate the given page frame.
     * @param frame the page frame to deallocate.
     */
    void deallocatePageFrame(void *frame);

private:
    common::BitSet frameOccupied;

    uintptr_t start;

    size_t pageFrameSize;

    /**
     * Convert from index of page frame to physical memory address.
     */
    void *fromIndex(size_t index);
};

}
