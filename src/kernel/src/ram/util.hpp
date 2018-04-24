#pragma once

#include <cstdint>

namespace myos::kernel::ram::util {

template<typename T>
T align(uint8_t bits, T x) {
    uintmax_t x_ = (uintmax_t) x;
    uintmax_t y = (((x_ - 1) >> bits) + 1) << bits;
    return (T) y;
}

}
