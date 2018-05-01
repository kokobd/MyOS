#pragma once

#include <cstddef>
#include <cstdint>

namespace myos::core::collections {

template<typename E>
class ArrayList {
public:
    ArrayList()
            : capacity(10), size_(0), data(nullptr) {
        auto *mem = new uint8_t[capacity * sizeof(E)];
        data = reinterpret_cast<E *>(mem);
    }

    ArrayList(const ArrayList &that);

    ArrayList &operator=(const ArrayList &that);

    ~ArrayList() {
        free();
    }

    void add(const E &elem);

    void remove(size_t index);

    size_t size() const {
        return size_;
    }

    bool isEmpty() const {
        return size() == 0;
    }

    E &operator[](size_t index) {
        return data[index];
    }

    const E &operator[](size_t index) const {
        return data[index];
    }

    E &first() {
        return data[0];
    }

    const E &last() const {
        return data[size_ - 1];
    }
private:
    E *data;
    size_t capacity;
    size_t size_;

    E *copy() const {
        auto *newData = reinterpret_cast<E *>(
                new uint8_t[capacity * sizeof(E)]
        );
        for (size_t i = 0; i < size(); ++i) {
            new(newData + i) E(data[i]);
        }
        return newData;
    }

    void free() {
        for (size_t i = 0; i < size_; ++i) {
            (data + i)->~E();
        }
        delete[] reinterpret_cast<uint8_t *>(data);
    }
};

template<typename E>
void ArrayList<E>::add(const E &elem) {
    if (size_ == capacity) {
        capacity = capacity + capacity / 2;
        E *newData = copy();
        free();
        data = newData;
    }

    new(data + size_) E(elem);
    ++size_;
}

template<typename E>
void ArrayList<E>::remove(size_t index) {
    if (index >= size())
        return;
    data[index].~E();
    for (size_t i = index; i < size() - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size_;
}

template<typename E>
ArrayList<E>::ArrayList(const ArrayList &that) {
    data = that.copy();
    size_ = that.size();
    capacity = that.capacity;
}

template<typename E>
ArrayList<E> &ArrayList<E>::operator=(const ArrayList &that) {
    E *newData = that.copy();
    size_t newSize = that.size();
    size_t newCapacity = that.capacity;

    free();

    data = newData;
    size_ = newSize;
    capacity = newCapacity;

    return *this;
}

}
