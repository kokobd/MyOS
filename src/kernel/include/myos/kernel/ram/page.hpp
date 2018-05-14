#pragma once

namespace myos::kernel::ram::page {

constexpr size_t PAGE_SIZE = 4096;

template<typename T>
constexpr T PAGE_SHIFT = 12;

}
