#pragma once

#include <cstddef>

namespace myos::core::memory::smart_pointers {

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

}
