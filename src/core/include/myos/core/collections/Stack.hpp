#pragma once

#include <cstddef>
namespace myos::base::collections {

template<typename E, size_t MAX_SIZE = 256>
class Stack {
public:
    Stack() : length(0) {}

    Stack(const Stack &another) = delete;

    Stack &operator=(const Stack &another) = delete;

    void push(const E &elem) {
        if (!full())
            data[length++] = elem;
    }

    E &top() {
        return const_cast<E &>(static_cast<const Stack &>(*this).top());
    }

    const E &top() const {
        return data[length - 1];
    }

    void pop() {
        if (!empty())
            --length;
    }

    size_t size() const {
        return length;
    }

    bool empty() const {
        return size() == 0;
    }

    bool full() const {
        return length == MAX_SIZE;
    }

private:
    E data[MAX_SIZE];

    size_t length;
};

}
