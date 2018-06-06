#pragma once

#include <cstdint>
#include <cstddef>
#include <myos/kernel/ipc/MsgBoxMetaInfo.hpp>

namespace myos::kernel::ipc {

class MessageBox {
public:
    explicit MessageBox(const MsgBoxMetaInfo &metaInfo);

    bool isEmpty() const {
        return tail == msgMaxCount;
    }

    bool isFull() const {
        if (!isEmpty())
            return next(tail) == head;
        else
            return false;
    }

    bool push(const void *message);

    bool pop(void *buffer);

    void moveData(void *newMemory);

    uintptr_t location() const {
        return reinterpret_cast<uintptr_t>(data);
    }

    size_t sizeInBytes() const {
        return static_cast<size_t>(msgSize) * static_cast<size_t>(msgMaxCount);
    }

private:
    const uint8_t msgSize;
    const uint8_t msgMaxCount;
    uint8_t head;
    uint8_t tail;

    uint8_t *data;

    uint8_t *at(uint8_t index);

    const uint8_t *at(uint8_t index) const;

    uint8_t next(uint8_t index) const;
};

}
