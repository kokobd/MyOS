#pragma once

#include "InterruptHandler.hpp"

namespace myos::kernel::cpu {

class NoopHandler : public InterruptHandler {
public:
    NoopHandler() = default;

    void handleInterrupt(InterruptType interrupt, const RegisterState &registerState) override;
};

}
