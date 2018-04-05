#include <cstring>

#include "shell.h"
#include "screen/vga.h"
#include "keyboard/input.h"

#define NS(X) kernel_shell_ ## X
#define vga(X) kernel_screen_vga_ ## X

static NS(Terminal) globalTerminal;

NS(Terminal) *NS(getGlobalTerminal)() {
    return &globalTerminal;
}

/**
 * Scroll down contents of the terminal.
 * Doesn't change cursor position.
 * @param this_ the terminal
 * @param lines the number of lines to scroll down.
 */
static void termScrollDown(NS(Terminal) *this__, size_t lines) {
    for (int32_t row = 0; row < this__->maxHeight - 1; ++row) {
        for (int32_t col = 0; col < this__->maxWidth; ++col) {
            vga(setChar)(row, col, vga(getChar)(row, col));
        }
    }
    for (int32_t col = 0; col < this__->maxWidth; ++col) {
        vga(setChar)(this__->maxHeight - 1, col, ' ');
    }
}

/**
 * Move the cursor to the beginning of next line
 * (Doesn't actually update hardware cursor)
 * @param this_ the terminal
 */
static void termNextLine(NS(Terminal) *this_) {
    this_->curX = 0;
    ++this_->curY;
    if (this_->curY == this_->maxHeight) {
        termScrollDown(this_, 1);
    }
}

/**
 * Move the cursor to the end of previous line
 * (Doesn't actually update hardware cursor)
 * @param this_ the terminal
 */
static void termPrevLine(NS(Terminal) *this_) {
    if (this_->curY == 0) {
        this_->curX = 0;
    } else {
        --this_->curY;
        this_->curX = this_->maxWidth - 1;
    }
}

static void termCursorMoveForward(NS(Terminal) *this_) {
    ++this_->curX;
    if (this_->curX == this_->maxWidth) {
        termNextLine(this_);
    }
}

static void termCursorMoveBackward(NS(Terminal) *this_) {
    if (this_->curX != 0) {
        --this_->curX;
    } else {
        termPrevLine(this_);
    }
}

inline static void termUpdateHWCursor(NS(Terminal) *this_) {
    kernel_screen_vga_moveCursor(this_->curX, this_->curY);
}

void NS(termInit)(NS(Terminal) *this_) {
    this_->curX = 0;
    this_->curY = 0;
    this_->maxWidth = kernel_screen_vga_getWidth();
    this_->maxHeight = kernel_screen_vga_getHeight();
    this_->bufferBegin = this_->inputBuffer;
    this_->bufferEnd = this_->inputBuffer;
    memset(this_->inputBuffer, 0, NS(INPUT_BUFFER_SIZE));

    termUpdateHWCursor(this_);
}

static inline bool bufferIsEmpty(NS(Terminal) *this_) {
    return this_->bufferBegin == this_->bufferEnd;
}

/**
 * Print a character without updating the hardware cursor.
 * @param this_ the terminal
 * @param ch the character to print
 */
static void termPutChar_(NS(Terminal) *this_, char ch) {
    if (ch == '\n') {
        termNextLine(this_);
    } else if (ch == '\b') {
        // move back the cursor, then put a ' '
        termCursorMoveBackward(this_);
        vga(setChar)(this_->curY, this_->curX, ' ');
    } else {
        vga(setChar)(this_->curY, this_->curX, ch);
        termCursorMoveForward(this_);
    }
}

void NS(termPutChar)(NS(Terminal) *this_, char ch) {
    termPutChar_(this_, ch);
    termUpdateHWCursor(this_);
}

void NS(termPutString)(NS(Terminal) *this_, const char *pt) {
    while (*pt != '\0') {
        termPutChar_(this_, *pt);
        ++pt;
    }
    termUpdateHWCursor(this_);
}

inline static void incBufferPt(NS(Terminal) *this_, char **pt) {
    ++(*pt);
    if (*pt - this_->inputBuffer == NS(INPUT_BUFFER_SIZE)) {
        *pt = this_->inputBuffer;
    }
}

static bool isBufferNotFull(NS(Terminal) *this_) {
    char *endNext = this_->bufferEnd;
    incBufferPt(this_, &endNext);
    return endNext != this_->bufferBegin;
}

static char termPopFromBuffer(NS(Terminal) *this_) {
    char next = *this_->bufferBegin;
    incBufferPt(this_, &(this_->bufferBegin));
    if (bufferIsEmpty(this_)) {
        this_->bufferReady = false;
    }
    return next;
}

static void termEraseLastFromBuffer(NS(Terminal) *this_) {
    if (bufferIsEmpty(this_))
        return;
    if (this_->bufferEnd == this_->inputBuffer) {
        this_->bufferEnd = this_->inputBuffer + NS(INPUT_BUFFER_SIZE) - 1;
    } else {
        --this_->bufferEnd;
    }

    if (bufferIsEmpty(this_)) {
        this_->bufferReady = false;
    }
}

char NS(termGetChar)(NS(Terminal) *this_) {
    if (!this_->bufferReady) {
        // read a line into buffer
        char next;
        do {
            next = kernel_keyboard_input_getChar();
            if (next == 0)
                continue;
            if (next != '\b') {
                *(this_->bufferEnd) = next;
                incBufferPt(this_, &(this_->bufferEnd));
            } else {
                termEraseLastFromBuffer(this_);
            }

            NS(termPutChar)(this_, next);
        } while (next != '\n' && isBufferNotFull(this_));

        this_->bufferReady = true;
    }
    return termPopFromBuffer(this_);
}

size_t NS(termReadLine)(NS(Terminal) *this_, char *dest, size_t limit) {
    size_t actualLength = 0;
    char ch = '\0';
    while (ch != '\n' && actualLength < limit) {
        ch = NS(termGetChar)(this_);
        dest[actualLength++] = ch;
    }
    return actualLength;
}

// TODO remove this_
void NS(termSetArg)(NS(Terminal) *this_, const char *arg) {
    this_->arg = arg;
}
