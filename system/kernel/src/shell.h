#pragma once

#include <stdint.h>
#include <stdbool.h>

#pragma push_macro("NS")
#define NS(X) kernel_shell_ ## X

#define kernel_shell_INPUT_BUFFER_SIZE 128

typedef struct {
    int32_t curX;
    int32_t curY;
    int32_t maxWidth;
    int32_t maxHeight;
    char inputBuffer[kernel_shell_INPUT_BUFFER_SIZE];
    char *bufferBegin;
    char *bufferEnd;
    bool bufferReady;
} NS(Terminal);

/**
 * Initialize a terminal object.
 * @param term the terminal object.
 */
void NS(termInit)(NS(Terminal) *term);

/**
 * Write a character to the terminal. There is
 * no buffer for now, so it happens immediately.
 * @param term the terminal
 * @param ch a character to write to the standard output
 */
void NS(termPutChar)(NS(Terminal) *term, char ch);

/**
 * Read a character from the terminal.
 * Note that the terminal has line buffer
 * @param term the terminal
 * @return a character read from the standard input
 */
char NS(termGetChar)(NS(Terminal) *term);

#pragma pop_macro("NS")