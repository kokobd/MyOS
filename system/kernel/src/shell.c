#include <string.h>
#include "shell.h"
#include "screen/vga.h"
#include "keyboard/input.h"

#define NS(X) kernel_shell_ ## X
#define vga(X) kernel_screen_vga_ ## X

/**
 * Scroll down contents of the terminal.
 * Doesn't change curser position.
 * @param this the terminal
 * @param lines the number of lines to scroll down.
 */
static void termScrollDown(NS(Terminal) *this, size_t lines) {
    for (int32_t row = 0; row < this->maxHeight - 1; ++row) {
        for (int32_t col = 0; col < this->maxWidth; ++col) {
            vga(setChar)(row, col, vga(getChar)(row, col));
        }
    }
    for (int32_t col = 0; col < this->maxWidth; ++col) {
        vga(setChar)(this->maxHeight - 1, col, ' ');
    }
}

/**
 * Move the cursor to the beginning of next line
 * (Doesn't actually update hardware cursor)
 * @param this the terminal
 */
static void termNextLine(NS(Terminal) *this) {
    this->curX = 0;
    ++this->curY;
    if (this->curY == this->maxHeight) {
        termScrollDown(this, 1);
    }
}

/**
 * Move the cursor to the end of previous line
 * (Doesn't actually update hardware cursor)
 * @param this the terminal
 */
static void termPrevLine(NS(Terminal) *this) {
    if (this->curY == 0) {
        this->curX = 0;
    } else {
        --this->curY;
        this->curX = this->maxWidth - 1;
    }
}

static void termCursorMoveForward(NS(Terminal) *this) {
    ++this->curX;
    if (this->curX == this->maxWidth) {
        termNextLine(this);
    }
}

static void termCursorMoveBackward(NS(Terminal) *this) {
    if (this->curX != 0) {
        --this->curX;
    } else {
        termPrevLine(this);
    }
}

inline static void termUpdateHWCursor(NS(Terminal) *this) {
    kernel_screen_vga_moveCursor(this->curX, this->curY);
}

void NS(termInit)(NS(Terminal) *this) {
    this->curX = 0;
    this->curY = 0;
    this->maxWidth = kernel_screen_vga_getWidth();
    this->maxHeight = kernel_screen_vga_getHeight();
    this->bufferBegin = this->inputBuffer;
    this->bufferEnd = this->inputBuffer;
    memset(this->inputBuffer, 0, NS(INPUT_BUFFER_SIZE));
}

static inline bool bufferIsEmpty(NS(Terminal) *this) {
    return this->bufferBegin == this->bufferEnd;
}

void NS(termPutChar)(NS(Terminal) *this, char ch) {
    if (ch == '\n') {
        termNextLine(this);
    } else if (ch == '\b') {
        // move back the cursor, then put a ' '
        termCursorMoveBackward(this);
        vga(setChar)(this->curX, this->curY, ' ');
    } else {
        vga(setChar)(this->curX, this->curY, ch);
        termCursorMoveForward(this);
    }
    termUpdateHWCursor(this);
}

inline static void incBufferPt(NS(Terminal) *this, char **pt) {
    ++(*pt);
    if (*pt - this->inputBuffer == NS(INPUT_BUFFER_SIZE)) {
        *pt = this->inputBuffer;
    }
}

static bool isBufferNotFull(NS(Terminal) *this) {
    char *endNext = this->bufferEnd;
    incBufferPt(this, &endNext);
    return endNext != this->bufferBegin;
}

static char termPopFromBuffer(NS(Terminal) *this) {
    char next = *this->bufferBegin;
    incBufferPt(this, &(this->bufferBegin));
    if (bufferIsEmpty(this)) {
        this->bufferReady = false;
    }
    return next;
}

char NS(termGetChar)(NS(Terminal) *this) {
    if (!this->bufferReady) {
        // read a line into buffer
        char next;
        do {
            next = kernel_keyboard_input_getChar();
            if (next != '\b') {
                *(this->bufferEnd) = next;
                incBufferPt(this, &(this->bufferEnd));
            } else {
                termPopFromBuffer(this);
            }

            NS(termPutChar)(this, next);
        } while (next != '\n' && isBufferNotFull(this));

        this->bufferReady = true;
    }
    return termPopFromBuffer(this);
}