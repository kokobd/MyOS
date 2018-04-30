#include <myos/core/memory.hpp>
#include <myos/core/memory/Heap.hpp>

namespace myos::core::memory {

namespace {
Heap *heap = nullptr;
}

void setHeap(Heap *heap_) {
    heap = heap_;
}

void *malloc(size_t size) {
    return heap->allocate(size);
}

void free(void *pt) {
    heap->deallocate(pt);
}

}