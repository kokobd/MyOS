#pragma once

#include <stdbool.h>

#pragma push_macro("NS")
#define NS(X) kernel_screen_vga_ ## X

inline static NS(getWidth)() {
    return 80;
}

inline static NS(getHeight)() {
    return 25;
}

bool NS(setChar)(int row, int col, char ch);

typedef enum {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
    RED = 4, MAGENTA = 5, BROWN = 6, WHITE = 7
} NS(Color);

bool NS(changeAttribute)(
        int row, int col,
        bool blink,
        bool foregroundIntensity,
        NS(Color) foregroundColor,
        NS(Color) backgroundColor);

#pragma pop_macro("NS")
