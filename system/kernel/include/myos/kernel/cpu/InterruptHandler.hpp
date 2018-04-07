#pragma once

#include <cstdint>

namespace myos::kernel::cpu {

class InterruptHandler {
public:
    InterruptHandler() : interruptNumber(0), hasErrorCode_(false) {}

    virtual void handleInterrupt() = 0;

    uint8_t getInterruptNumber() {
        return interruptNumber;
    }

    bool hasErrorCode() {
        return this->hasErrorCode_;
    }

    virtual ~InterruptHandler() = default;

private:
    uint8_t interruptNumber;
    bool hasErrorCode_;

protected:
    void setInterruptNumber(uint8_t interrupt) {
        this->interruptNumber = interrupt;
    }

    void setHasErrorCode(bool hasErrorCode) {
        this->hasErrorCode_ = hasErrorCode_;
    }
};

}
