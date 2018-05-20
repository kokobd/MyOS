#pragma once

#include <cstdint>
#include <cstddef>
#include "shared_ptr.hpp"

namespace myos::core::memory::smart_pointers {

template<typename T>
class weak_ptr {
public:
    constexpr weak_ptr() : obj(nullptr), refCounter(nullptr) {}

    constexpr weak_ptr(nullptr_t) : weak_ptr() {}

    weak_ptr(const shared_ptr <T> &pt)
            : obj(pt.obj), refCounter(pt.refCounter) {
        if (refCounter)
            refCounter->increaseWeakCount();
    }

private:
    template<typename Y>
    void copy(const weak_ptr<Y> &that) {
        obj = that.obj;
        refCounter = that.refCounter;
        refCounter->increaseWeakCount();
    }

public:
    weak_ptr(const weak_ptr<T> &rhs) {
        copy(rhs);
    }

    template<typename Y>
    weak_ptr(const weak_ptr<Y> &rhs) {
        copy(rhs);
    }

private:
    template<typename Y>
    void copyAssignment(const weak_ptr<Y> &that) {
        if (this != &that) {
            free();
            copy(that);
        }
    }

public:
    template<typename Y>
    weak_ptr<T> &operator=(const weak_ptr<Y> &rhs) {
        copyAssignment(rhs);
        return *this;
    }

    weak_ptr<T> &operator=(const weak_ptr<T> &rhs) {
        copyAssignment(rhs);
        return *this;
    }

private:
    template<typename Y>
    void move(weak_ptr<Y> &&that) noexcept {
        obj = that.obj;
        refCounter = that.refCounter;
        that.obj = nullptr;
        that.refCounter = nullptr;
    }

public:
    template<typename Y>
    weak_ptr(weak_ptr<Y> &&that) noexcept {
        move(utility::move(that));
    }

    weak_ptr(weak_ptr<T> &&that) noexcept {
        move(utility::move(that));
    }

private:
    template<typename Y>
    void moveAssignment(weak_ptr<Y> &&that) noexcept {
        if (this != &that) {
            free();
            move(utility::move(that));
        }
    }

public:
    template<typename Y>
    weak_ptr<T> &operator=(weak_ptr<Y> &&rhs) noexcept {
        moveAssignment(utility::move(rhs));
        return *this;
    }

    weak_ptr<T> &operator=(weak_ptr<T> &&rhs) noexcept {
        moveAssignment(utility::move(rhs));
        return *this;
    }

private:
    void free() {
        if (refCounter) {
            refCounter->decreaseWeakCount();
            if (refCounter->weakCount() == 0 && refCounter->useCount() == 0) {
                delete refCounter;
            }
        }
    }

public:
    ~weak_ptr() {
        free();
    }

public:
    uint32_t use_count() const {
        return refCounter ? refCounter->useCount() : 0;
    }

    bool expired() const {
        return use_count() == 0;
    }

    shared_ptr <T> lock() const noexcept {
        if (expired()) {
            return nullptr;
        }
        shared_ptr<T> ret;
        ret.obj = obj;
        ret.refCounter = refCounter;
        refCounter->increaseUseCount();
        return ret;
    }

private:
    T *obj;
    typename shared_ptr<T>::Counter *refCounter;
};

}

