#pragma once

#include <stdint.h>

#pragma push_macro("NS")
#define NS(X) kernel_shell_ ## X

#define kernel_shell_INPUT_BUFFER_SIZE 128

typedef struct {
    int32_t curX;
    int32_t curY;
    int32_t maxWidth;
    int32_t maxHeight;
    char inputBuffer[kernel_shell_INPUT_BUFFER_SIZE];
} NS(Terminal);

void NS(termPutChar)(NS(Terminal) *term, char ch);

char NS(termGetChar)(NS(Terminal) *term);

#pragma pop_macro("NS")
