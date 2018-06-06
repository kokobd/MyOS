#include <myos/kernel/ipc/MessageBox.hpp>
#include <cstring>

namespace myos::kernel::ipc {


MessageBox::MessageBox(const MsgBoxMetaInfo &metaInfo)
        : msgSize(metaInfo.msgSize),
          msgMaxCount(metaInfo.msgMaxCount) {
    head = 0;
    tail = msgMaxCount;
    data = static_cast<uint8_t *>(metaInfo.memory);
}

bool MessageBox::push(const void *message) {
    if (isFull()) {
        return false;
    }

    if (isEmpty()) {
        tail = head;
    } else {
        tail = next(tail);
    }
    memcpy(at(tail), message, msgSize);
    return true;
}

uint8_t *MessageBox::at(uint8_t index) {
    return const_cast<uint8_t *>(static_cast<const MessageBox &>(*this).at(index));
}

const uint8_t *MessageBox::at(uint8_t index) const {
    return data + (index * static_cast<size_t>(msgSize));
}

uint8_t MessageBox::next(uint8_t index) const {
    ++index;
    if (index == msgMaxCount) {
        index = 0;
    }
    return index;
}

bool MessageBox::pop(void *buffer) {
    if (isEmpty())
        return false;

    memcpy(buffer, at(head), msgSize);
    if (head == tail) {
        tail = msgMaxCount;
    } else {
        head = next(head);
    }
    return true;
}

void MessageBox::moveData(void *newMemory) {
    memcpy(newMemory, data, sizeInBytes());
}

}
