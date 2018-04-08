#pragma once

#include <cstdint>
#include "RegisterState.hpp"
#include "InterryptType.hpp"

namespace myos::kernel::cpu {

class InterruptHandler {
public:
    virtual void handleInterrupt(InterruptType interrupt, const RegisterState &registerState) = 0;

    virtual ~InterruptHandler() = default;

    uint32_t getReturnValue() const { return returnValue; }

private:
    uint32_t returnValue = 0;

protected:
    void setReturnValue(uint32_t returnValue) {
        this->returnValue = returnValue;
    }
};

}
