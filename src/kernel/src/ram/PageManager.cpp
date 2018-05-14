#include <myos/kernel/ram/PageManager.hpp>
#include <myos/core/memory.hpp>
#include <myos/kernel/ram/page.hpp>

using myos::core::memory::alignUp;

namespace myos::kernel::ram {

PageManager::PageManager(
        void *start, size_t count)
        : counters(count, 0) {
    start = alignUp(page::PAGE_SHIFT<uint32_t>, start);
    this->start = reinterpret_cast<uintptr_t>(start);
}

void *PageManager::newPage() {
    size_t index = counters.size();
    for (size_t i = 0; i != counters.size(); ++i) {
        if (counters[i] == 0) {
            index = counters[i];
            break;
        }
    }
    if (index == counters.size()) {
        return nullptr;
    } else {
        ++counters[index];
        return indexToAddress(index);
    }
}

void PageManager::deletePage(void *physicalAddress) {
    --processCount(physicalAddress);
}

void *PageManager::indexToAddress(size_t index) const {
    return reinterpret_cast<void *>(start + page::PAGE_SIZE * index);
}

uint32_t &PageManager::processCount(void *page) {
    return counters[addressToIndex(page)];
}

size_t PageManager::addressToIndex(void *address) const {
    return static_cast<size_t>(
            reinterpret_cast<uintptr_t>(address) - start
    );
}

const uint32_t &PageManager::processCount(void *page) const {
    return counters[addressToIndex(page)];
}

}
