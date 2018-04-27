#include <myos/base/memory.hpp>
#include <myos/base/memory/Heap.hpp>

namespace myos::base::memory {

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