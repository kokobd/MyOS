#pragma once

#include <cstdint>
#include "RegisterState.hpp"

namespace myos::kernel::cpu {

class InterruptHandler {
public:
    virtual void handleInterrupt(const RegisterState &registerState) = 0;

    virtual ~InterruptHandler() = default;

    uint8_t getInterruptNumber() const { return interrupt; };

    uint32_t getReturnValue() const { return returnValue; }

private:
    uint8_t interrupt = 0;
    uint32_t returnValue = 0;

protected:
    void setInterruptNumber(uint8_t interrupt) {
        this->interrupt = interrupt;
    }

    void setReturnValue(uint32_t returnValue) {
        this->returnValue = returnValue;
    }
};

}
