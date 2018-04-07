#pragma once

#include "InterruptHandler.hpp"

namespace myos::kernel::cpu {

class NoopHandler : public InterruptHandler {
public:
    NoopHandler(uint8_t interrupt);

    static NoopHandler &instance();

private:
    static NoopHandler handler; // TODO how can this be initialized?
};

}
