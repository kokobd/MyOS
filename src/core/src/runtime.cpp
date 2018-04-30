#include <cstddef>
#include <myos/core/memory.hpp>

using myos::core::memory::malloc;
using myos::core::memory::free;

void *operator new(size_t size) {
    return malloc(size);
}

void operator delete(void *pt) {
    free(pt);
}

void *operator new[](size_t size) {
    return malloc(size);
}

void operator delete[](void *pt) {
    free(pt);
}