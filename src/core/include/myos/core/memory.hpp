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
class shared_ptr;

template<typename T>
class unique_ptr {
    friend class shared_ptr<T>;

public:
    constexpr unique_ptr() noexcept
            : unique_ptr(nullptr) {}

    constexpr unique_ptr(nullptr_t) noexcept : obj(nullptr) {}

    unique_ptr(T *obj) noexcept : obj(obj) {}

    unique_ptr(const unique_ptr<T> &) = delete;

    unique_ptr<T> &operator=(const unique_ptr<T> &) = delete;

    unique_ptr(unique_ptr<T> &&that) noexcept
            : obj(that.obj) {
        that.obj = nullptr;
    }

    unique_ptr<T> &operator=(unique_ptr<T> &&that) noexcept {
        if (this != &that) {
            delete obj;
            that.obj = nullptr;
        }
        return *this;
    }

    ~unique_ptr() { delete obj; }

    explicit operator bool() const {
        return obj == nullptr;
    }

    T *get() {
        return obj;
    }

    const T *get() const {
        return obj;
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

    T *release() {
        T *ret = obj;
        obj = nullptr;
        return ret;
    }

    friend bool operator==(const unique_ptr<T> &lhs, const unique_ptr<T> &rhs) {
        return lhs.obj == rhs.obj;
    }

    friend bool operator!=(const unique_ptr<T> &lhs, const unique_ptr<T> &rhs) {
        return lhs.obj != rhs.obj;
    }

private:
    T *obj;
};

template<typename Y>
class weak_ptr;

template<typename T>
class shared_ptr {
    template<typename Y>
    friend
    class weak_ptr;

public:
    template<typename Y>
    explicit shared_ptr(Y *obj)
            : obj(obj) {
        refCount = new uint32_t(1);
    }

    constexpr shared_ptr() noexcept
            : obj(nullptr), refCount(nullptr) {}

    constexpr shared_ptr(nullptr_t) noexcept
            : obj(nullptr), refCount(nullptr) {}

private:
    template<typename Y>
    void copy(const shared_ptr<Y> &that) {
        obj = that.obj;
        refCount = that.refCount;
        if (refCount)
            ++(*refCount);
    }

public:
    template<typename Y>
    shared_ptr(const shared_ptr<Y> &that) {
        copy(that);
    }

    shared_ptr(const shared_ptr<T> &that) {
        copy(that);
    }

private:
    template<typename Y>
    void copyAssignment(const shared_ptr<Y> &that) {
        if (this != &that) {
            free();
            copy(that);
        }
    }

public:
    template<typename Y>
    shared_ptr<T> &operator=(const shared_ptr<Y> &rhs) {
        copyAssignment(rhs);
        return *this;
    }

    shared_ptr<T> &operator=(const shared_ptr<T> &rhs) {
        copyAssignment(rhs);
        return *this;
    }

private:
    template<typename Y>
    void move(shared_ptr<Y> &&that) noexcept {
        if (this != &that) {
            obj = that.obj;
            refCount = that.refCount;
            that.obj = nullptr;
            that.refCount = nullptr;
        }
    }

public:
    template<typename Y>
    shared_ptr(shared_ptr<Y> &&that) noexcept {
        move(utility::move(that));
    }

    shared_ptr(shared_ptr<T> &&that) noexcept {
        move(utility::move(that));
    }

private:
    template<typename Y>
    void moveAssignment(shared_ptr<Y> &&that) noexcept {
        if (this != &that) {
            free();
            move(utility::move(that));
        }
    }

public:
    template<typename Y>
    shared_ptr<T> &operator=(shared_ptr<Y> &&rhs) noexcept {
        moveAssignment(utility::move(rhs));
        return *this;
    }

    shared_ptr<T> &operator=(shared_ptr<T> &&rhs) noexcept {
        moveAssignment(utility::move(rhs));
        return *this;
    }

public:
    ~shared_ptr() {
        free();
    }

    template<typename Y>
    shared_ptr(unique_ptr<Y> &&rhs) : obj(rhs.release()) {
        refCount = new uint32_t(1);
    }

    template<typename Y>
    shared_ptr<T> &operator=(unique_ptr<Y> &&rhs) {
        free();
        obj = rhs.release();
        refCount = new uint32_t(1);
        return *this;
    }

    friend bool operator==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
        return lhs.obj == rhs.obj;
    }

    friend bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
        return lhs.obj != rhs.obj;
    }

    explicit operator bool() const {
        return refCount != nullptr;
    }

    T *get() {
        return obj;
    }

    const T *get() const {
        return obj;
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

    uint32_t use_count() const {
        return refCount ? *refCount : 0;
    }

private:
    void free();

private:
    T *obj;
    uint32_t *refCount;
};

//template<typename T>
//class weak_ptr {
//public:
//    constexpr weak_ptr() : obj(nullptr), refCount(nullptr) {}
//
//    constexpr weak_ptr(nullptr_t) : weak_ptr() {}
//
//    weak_ptr(const shared_ptr<T> &pt)
//            : obj(pt.obj), refCount(pt.refCount) {}
//
//public:
//    weak_ptr(const weak_ptr<T> &rhs) = default;
//
//    weak_ptr<T> &operator=(const weak_ptr<T> &rhs) = default;
//
//    weak_ptr(weak_ptr<T> &&rhs) noexcept = default;
//
//    weak_ptr<T> &operator=(weak_ptr<T> &&rhs) noexcept = default;
//
//    ~weak_ptr() = default;
//
//public:
//    uint32_t use_count() const {
//        return refCount ? *refCount : 0;
//    }
//
//    bool expired() const {
//        return use_count() == 0;
//    }
//
//    shared_ptr<T> lock() const noexcept {
//        if (expired()) {
//            return nullptr;
//        }
//        shared_ptr<T> ret;
//        ret.obj = obj;
//        ret.refCount = refCount;
//        ++(*refCount);
//        return ret;
//    }
//
//private:
//    T *obj;
//    uint32_t *refCount;
//};

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

}