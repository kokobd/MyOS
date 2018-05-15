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
constexpr T log2(T x) {
    return x > 1 ? 1 + log2(x >> 1) : 0;
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

template<typename T>
class shared_ptr {
public:
    explicit shared_ptr(T *obj);

    shared_ptr() noexcept;

    shared_ptr(nullptr_t) noexcept;

    shared_ptr(const shared_ptr<T> &that);

    shared_ptr<T> &operator=(const shared_ptr<T> &rhs);

    shared_ptr(shared_ptr &&that) noexcept;

    shared_ptr<T> &operator=(shared_ptr<T> &&rhs) noexcept;

    ~shared_ptr();

    friend bool operator==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
        return lhs.obj == rhs.obj;
    }

    explicit operator bool() const {
        return refCount != nullptr;
    }

    T &operator*() {
        return *obj;
    }

    const T &operator*() const {
        return *obj;
    }

    T *operator->() {
        return obj;
    }

    const T *operator->() const {
        return obj;
    }

private:
    void free();

private:
    T *obj;
    uint32_t *refCount;
};

template<typename T>
shared_ptr<T>::shared_ptr(T *obj)
        : obj(obj) {
    refCount = new uint32_t(1);
}

template<typename T>
shared_ptr<T>::~shared_ptr() {
    free();
}

template<typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> &that)
        : obj(that.obj), refCount(that.refCount) {
    ++(*refCount);
}

template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> &&that) noexcept
        : obj(that.obj), refCount(that.refCount) {
    that.refCount = nullptr;
    that.obj = nullptr;
}

template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &rhs) {
    if (this != &rhs) {
        free();
        this->obj = rhs.obj;
        this->refCount = rhs.refCount;
        ++(*refCount);
    }
    return *this;
}

template<typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&rhs) noexcept {
    if (this != &rhs) {
        free();
        obj = rhs.obj;
        refCount = rhs.refCount;
        ++(*refCount);
    }
    return *this;
}

template<typename T>
void shared_ptr<T>::free() {
    if (refCount != nullptr) {
        --(*refCount);
        if (*refCount == 0) {
            delete obj;
            delete refCount;
        }
    }
}

template<typename T>
shared_ptr<T>::shared_ptr() noexcept
        : obj(nullptr), refCount(nullptr) {}

template<typename T>
shared_ptr<T>::shared_ptr(nullptr_t) noexcept
        : shared_ptr() {}

}