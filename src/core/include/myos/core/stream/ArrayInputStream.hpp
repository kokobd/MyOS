#pragma once

#include <myos/core/stream/InputStream.hpp>
#include <cstdint>
#include <cstddef>

namespace myos::core::stream {

template<typename E>
class ArrayInputStream : public InputStream<E> {
public:
    ArrayInputStream(E *ptr, size_t size);

    ArrayInputStream(E *begin, E *end);

    bool hasNext() const override;

    E &next() override;

private:
    E *begin;
    E *end;
};

template<typename E>
ArrayInputStream<E>::ArrayInputStream(E *ptr, size_t size)
        : ArrayInputStream(ptr, ptr + size) {
}

template<typename E>
bool ArrayInputStream<E>::hasNext() const {
    return begin != end;
}

template<typename E>
E &ArrayInputStream<E>::next() {
    return *begin++;
}

template<typename E>
ArrayInputStream<E>::ArrayInputStream(E *begin, E *end)
        : begin(begin), end(end) {
    if (begin == nullptr || end == nullptr) {
        this->begin = nullptr;
        this->end = nullptr;
    }
}

}