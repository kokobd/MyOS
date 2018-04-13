#pragma once

#include <cstddef>

namespace myos::kernel::common {

template<typename E, size_t MAX_SIZE = 256>
class Queue {
public:
    Queue() : begp(data), endp(begp) {}

    constexpr size_t maxSize() const { return MAX_SIZE; }

    bool empty() const {
        return endp == begp;
    }

    size_t size() const {
        if (endp >= begp) {
            return endp - begp;
        }
        return (MAX_SIZE + 1) - (begp - endp);
    }

    void pushBack(const E &elem) {
        *endp = elem;
        endp = next(endp);
    }

    void popFront() {
        if (empty())
            return;
        begp = next(begp);
    }

    E &front() {
        return const_cast<E &>(static_cast<const Queue *>(this)->front());
    }

    const E &front() const {
        return *begp;
    }

    E &back() {
        return const_cast<E &>(static_cast<const Queue *>(this)->back());
    }

    const E &back() const {
        return *prev(endp);
    }


private:
    E data[MAX_SIZE + 1];
    E *begp; // including
    E *endp; // excluding

    E *next(E *pt) const {
        return const_cast<E *>(this->next(static_cast<const E *>(pt)));
    }

    const E *next(const E *pt) const {
        if (pt == data + MAX_SIZE) {
            pt = data;
        } else {
            ++pt;
        }
        return pt;
    }

    E *prev(E *pt) const {
        return const_cast<E *>(this->prev(static_cast<const E *>(pt)));
    }

    const E *prev(const E *pt) const {
        if (pt == data) {
            pt = data + MAX_SIZE;
        } else {
            --pt;
        }
        return pt;
    }
};

}
