#include <myos/kernel/ram/PageFrameManager.hpp>
#include "util.hpp"

namespace myos::kernel::ram {

PageFrameManager::PageFrameManager(
        void *start, size_t pageFrameSize, size_t count)
        : frameOccupied(count), pageFrameSize(pageFrameSize) {
    // Assumes pageFrameSize is an exponent of 2
    size_t mask = 1;
    uint8_t bits = 0;
    while (mask != 0 && !(pageFrameSize & mask)) {
        ++bits;
        mask = mask << 1;
    }
    start = util::align(bits, start); // align to 4KiB
    this->start = reinterpret_cast<uintptr_t>(start);
}

void *PageFrameManager::allocatePageFrame() {
    size_t index = frameOccupied.findFirst(false);
    frameOccupied.set(index);
    void *frame = fromIndex(index);
    return frame;
}

void PageFrameManager::deallocatePageFrame(void *frame) {
    size_t index = (reinterpret_cast<uintptr_t>(frame) - start) / pageFrameSize;
    frameOccupied.set(index, false);
}

void *PageFrameManager::fromIndex(size_t index) {
    return reinterpret_cast<void *>(start + pageFrameSize * index);
}

}
