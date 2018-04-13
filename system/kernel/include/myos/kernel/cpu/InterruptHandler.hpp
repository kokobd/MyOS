#pragma once

#include <cstdint>
#include "InterryptType.hpp"

namespace myos::kernel::cpu {

class RegisterState;

class InterruptHandler {
public:
    virtual void handleInterrupt(InterruptType interrupt, RegisterState &registerState) = 0;

    virtual ~InterruptHandler() = default;
};

}
