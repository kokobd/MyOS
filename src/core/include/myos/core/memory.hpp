#pragma once

#include <cstddef>
#include <cstdint>
#include <myos/core/utility.hpp>

namespace myos::core::memory {

void *malloc(size_t size);

void free(void *pt);

class Heap;

/**
 * Changes the heap implementation used by
 * default new/delete/malloc/free.
 * Only works if we compile to target platform.
 *
 * Note that the library will automatically call this function
 * with a reasonable implementation, prior to the execution of
 * your main().
 * @param heap the heap implementation to use.
 */
void setHeap(Heap *heap);

template<typename T>
constexpr uint8_t log2(T x) {
    return static_cast<uint8_t>(x > 1 ? 1 + log2(x >> 1) : 0);
}

/**
 * Align an integral value.
 * @tparam T the integral type
 * @param bits number of bits to align.
 * @param x the value to align
 * @return the aligned value. Gur
 */
template<typename T>
inline T alignUp(uint8_t bits, T x) {
    uintmax_t x_ = (uintmax_t) x;
    uintmax_t y = (((x_ - 1) >> bits) + 1) << bits;
    return (T) y;
}

template<typename T>
inline T alignUpWord(T x) {
#ifdef __i386__
#define WORD_SIZE 4
#else
#define WORD_SIZE 8
#endif
    return alignUp(memory::log2(WORD_SIZE), x);
}

}
