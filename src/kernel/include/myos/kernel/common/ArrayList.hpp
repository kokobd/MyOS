#pragma once

#include <cstddef>

namespace myos::kernel::common {

template<typename E>
class ArrayList {
public:
    ArrayList();

    void append(const E &elem);

    bool empty() const;

    size_t size() const;

private:
    E *data;
    size_t capacity;
    size_t length;
};

template<typename E>
ArrayList<E>::ArrayList(): capacity(8), length(0) {
    data = new E[capacity];

}

}
