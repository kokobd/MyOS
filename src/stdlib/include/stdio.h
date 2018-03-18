#ifndef MYOS_STDIO_H_
#define MYOS_STDIO_H_

#include <stdbool.h>
#include <stdint.h>

bool putchar(int row, int col, char ch);

enum Color {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
    RED = 4, MAGENTA = 5, BROWN = 6, WHITE = 7
};

bool changeAttribute(
    int row, int col,
    bool blink,
    bool foregroundIntensity,
    enum Color foregroundColor,
    enum Color backgroundColor);

typedef unsigned int size_t;

/**
  Return size of the file.
 */
size_t loadFile(const char *fileName, uint8_t *buffer);

#endif