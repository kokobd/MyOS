#pragma once

#include <cstdint>

namespace myos::kernel::drivers {

class VGAScreen {
public:
    VGAScreen()
            : VIDEO_ADDR(reinterpret_cast<uint8_t *const>(0xb8000)) {}

    uint32_t getWidth() const {
        return 80;
    }

    uint32_t getHeight() const {
        return 25;
    }

    bool setChar(uint32_t row, uint32_t col, char ch);

    char getChar(uint32_t row, uint32_t col) const;

    enum Color {
        BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
        RED = 4, MAGENTA = 5, BROWN = 6, WHITE = 7
    };

    bool changeAttribute(uint32_t row, uint32_t col,
                         bool blink, bool foregroundIntensity,
                         Color foregroundColor,
                         Color backgroundColor);

    void moveCursor(uint32_t row, uint32_t col);

private:
    bool checkBoundary(uint32_t row, uint32_t col) {
        return row < getWidth() && col < getHeight();
    }

    void *const VIDEO_ADDR;
};

}
