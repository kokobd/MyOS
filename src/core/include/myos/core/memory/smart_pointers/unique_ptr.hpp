#pragma once

#include <cstddef>
#include <myos/core/utility.hpp>

namespace myos::core::memory::smart_pointers {

template<typename T>
class shared_ptr;

template<typename T>
class unique_ptr {
    friend class shared_ptr<T>;

    template<typename Y>
    friend
    class unique_ptr;

public:
    constexpr unique_ptr() noexcept
            : unique_ptr(nullptr) {}

    constexpr unique_ptr(nullptr_t) noexcept : obj(nullptr) {}

    template<typename Y>
    explicit unique_ptr(Y *obj) noexcept : obj(obj) {}

    unique_ptr(const unique_ptr<T> &) = delete;

    unique_ptr<T> &operator=(const unique_ptr<T> &) = delete;

private:
    template<typename Y>
    void move(unique_ptr<Y> &&that) noexcept {
        obj = that.obj;
        that.obj = nullptr;
    }

public:
    template<typename Y>
    unique_ptr(unique_ptr<Y> &&that) noexcept {
        move(utility::move(that));
    }

    unique_ptr(unique_ptr<T> &&that) noexcept {
        move(utility::move(that));
    }

private:
    template<typename Y>
    void moveAssignment(unique_ptr<Y> &&that) noexcept {
        if (this != &that) {
            release();
            that.obj = nullptr;
        }
    }

public:
    template<typename Y>
    unique_ptr<T> &operator=(unique_ptr<Y> &&that) noexcept {
        moveAssignment(utility::move(that));
        return *this;
    }

    unique_ptr<T> &operator=(unique_ptr<T> &&that) noexcept {
        moveAssignment(utility::move(that));
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
