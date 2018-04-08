#include <cstddef>

extern "C" void __cxa_pure_virtual() {
    // No op
}

void operator delete(void *, size_t) {
    // TODO
}
