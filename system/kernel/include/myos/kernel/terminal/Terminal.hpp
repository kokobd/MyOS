#pragma once

#include <cstddef>
#include <cstdint>
#include <myos/kernel/common/Queue.hpp>
#include <myos/kernel/drivers/VGAScreen.hpp>

namespace myos::kernel::drivers::terminal {

class Terminal {
private:
    VGAScreen &screen;
public:
    explicit Terminal(VGAScreen &screen);

    void putChar(char ch);

    void putString(const char *c_str);

    char getChar();

private:
    uint32_t curX;
    uint32_t curY;
    uint32_t maxWidth;
    uint32_t maxHeight;

    common::Queue<char> inputBuffer;
    bool inputBufferReady;

};

}
