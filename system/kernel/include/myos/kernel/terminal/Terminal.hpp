#pragma once

#include <cstddef>
#include <cstdint>
#include <myos/kernel/common/Queue.hpp>

namespace myos::kernel::drivers::terminal {

class Terminal {
public:
    Terminal() = default;

private:
    int32_t curX;
    int32_t curY;
    int32_t maxWidth;
    int32_t maxHeight;


};

}
