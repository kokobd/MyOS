#include <myos/kernel/drivers/VGAScreen.hpp>
#include <myos/kernel/drivers/util.hpp>

namespace myos::kernel::drivers {

bool VGAScreen::setChar(uint32_t row, uint32_t col, char ch) {
    if (!checkBoundary(row, col))
        return false;
    *(reinterpret_cast<char *>(VIDEO_ADDR) + (80 * row + col) * 2) = ch;
    return true;
}

char VGAScreen::getChar(uint32_t row, uint32_t col) const {
    return *(reinterpret_cast<char *>(VIDEO_ADDR) + (80 * row + col) * 2);
}

bool VGAScreen::changeAttribute(uint32_t row, uint32_t col,
                                bool blink, bool foregroundIntensity,
                                VGAScreen::Color foregroundColor,
                                VGAScreen::Color backgroundColor) {
    if (!checkBoundary(row, col))
        return false;
    uint8_t attribute = 0;
    if (blink)
        attribute |= 0b10000000U;
    if (foregroundIntensity)
        attribute |= 0b00001000U;
    attribute |= (foregroundColor & 0b00000111U);
    attribute |= ((backgroundColor << 4) & 0b01110000U);
    *(reinterpret_cast<uint8_t *>(VIDEO_ADDR) + (80 * row + col) * 2 + 1) = attribute;

    return true;
}

void VGAScreen::moveCursor(uint32_t row, uint32_t col) {
    uint32_t pos = row * getWidth() + col;

    using util::outb;
    outb(0x3D4, 0x0F);
    outb(0x3D5, static_cast<uint8_t>(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, static_cast<uint8_t>((pos >> 8) & 0xFF));
}

}
