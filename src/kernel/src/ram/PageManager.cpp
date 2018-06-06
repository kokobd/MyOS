#include <myos/kernel/ram/PageManager.hpp>
#include <myos/core/memory.hpp>

using myos::core::memory::alignUp;
using myos::core::memory::log2;

namespace myos::kernel::ram {

PageManager::PageManager(
        uintptr_t start, size_t pageSize, size_t count)
        : counters(count, 0), PAGE_SIZE(pageSize) {
    start = alignUp(log2(pageSize), start);
    this->start = reinterpret_cast<uintptr_t>(start);
}

uintptr_t PageManager::newPage() {
    size_t index = counters.size();
    for (size_t i = 0; i != counters.size(); ++i) {
        if (counters[i] == 0) {
            index = i;
            break;
        }
    }
    if (index == counters.size()) {
        return 0;
    } else {
        ++counters[index];
        return indexToAddress(index);
    }
}

void PageManager::releasePage(uintptr_t physicalAddress) {
    --processCount(physicalAddress);
}

uintptr_t PageManager::indexToAddress(size_t index) const {
    return start + PAGE_SIZE * index;
}

uint32_t &PageManager::processCount(uintptr_t physicalAddress) {
    return counters[addressToIndex(physicalAddress)];
}

size_t PageManager::addressToIndex(uintptr_t address) const {
    return static_cast<size_t>(
            reinterpret_cast<uintptr_t>(address) - start
    );
}

const uint32_t &PageManager::processCount(uintptr_t physicalAddress) const {
    return counters[addressToIndex(physicalAddress)];
}

}
