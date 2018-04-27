#include <cstddef>
#include <myos/base/memory.hpp>

using myos::base::memory::malloc;
using myos::base::memory::free;

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