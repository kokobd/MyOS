#include <stdio.h>

static char * const video = (char *) 0xb8000;

static inline bool checkBoundary(int row, int col) {
    return row >= 0 && row < 25 && col >= 0 && col < 80;
}

bool putchar(int row, int col, char ch) {
    if (!checkBoundary(row, col))
        return false;
    *(video + (80 * row + col) * 2) = ch;
    return true;
}

bool changeAttribute(
    int row, int col,
    bool blink,
    bool foregroundIntensity,
    enum Color foregroundColor,
    enum Color backgroundColor)
{
    if (!checkBoundary(row, col))
        return false;
    unsigned char attribute = 0;
    if (blink)
        attribute |= 0b10000000;
    if (foregroundIntensity)
        attribute |= 0b00001000;
    attribute |= (foregroundColor & 0b00000111);
    attribute |= ((backgroundColor << 4) & 0b01110000);
    *(video + (80 * row + col) * 2 + 1) = attribute;

    putchar(0, 0, attribute);

    return true;
}