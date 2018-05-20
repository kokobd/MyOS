#pragma once

#include <cstdint>
#include <cstddef>
#include "unique_ptr.hpp"
#include <myos/core/utility.hpp>

namespace myos::core::memory::smart_pointers {

template<typename Y>
class weak_ptr;

template<typename T>
class shared_ptr {
    template<typename Y>
    friend
    class weak_ptr;

    class Counter {
    public:
    public:
        Counter() : use_count(1), weak_count(0) {}

        Counter(const Counter &) = delete;

        Counter(Counter &&) = delete;

        Counter &operator=(const Counter &) = delete;

        Counter &operator=(Counter &&) = delete;

        ~Counter() = default;

        void increaseUseCount() {
            ++use_count;
        }

        void decreaseUseCount() {
            --use_count;
        }

        void increaseWeakCount() {
            ++weak_count;
        }

        void decreaseWeakCount() {
            --weak_count;
        }

        uint32_t useCount() const { return use_count; }

        uint32_t weakCount() const { return weak_count; }

    private:
        uint32_t use_count;
        uint32_t weak_count;
    };

public:
    template<typename Y>
    explicit shared_ptr(Y *obj)
            : obj(obj) {
        refCounter = new Counter();
    }

    constexpr shared_ptr() noexcept
            : obj(nullptr), refCounter(nullptr) {}

    constexpr shared_ptr(nullptr_t) noexcept
            : obj(nullptr), refCounter(nullptr) {}

private:
    template<typename Y>
    void copy(const shared_ptr<Y> &that) {
        obj = that.obj;
        refCounter = that.refCounter;
        if (refCounter)
            refCounter->increaseUseCount();
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
            refCounter = that.refCounter;
            that.obj = nullptr;
            that.refCounter = nullptr;
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
        refCounter = new Counter();
    }

    template<typename Y>
    shared_ptr<T> &operator=(unique_ptr<Y> &&rhs) {
        free();
        obj = rhs.release();
        refCounter = new Counter();
        return *this;
    }

    friend bool operator==(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
        return lhs.obj == rhs.obj;
    }

    friend bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) {
        return lhs.obj != rhs.obj;
    }

    explicit operator bool() const {
        return refCounter != nullptr;
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
        return refCounter ? refCounter->useCount() : 0;
    }

private:
    void free() {
        if (refCounter != nullptr) {
            refCounter->decreaseUseCount();
            if (refCounter->useCount() == 0) {
                delete obj;
                if (refCounter->weakCount() == 0) {
                    delete refCounter;
                }
            }
        }
    }

private:
    T *obj;
    Counter *refCounter;
};


}
