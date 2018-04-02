#include "shell.h"
#include "screen/vga.h"

#define NS(X) kernel_shell_ ## X
#define vga(X) kernel_screen_vga_ ## X

/**
 * Scroll down contents of the terminal.
 * Doesn't change curser position.
 * @param this the terminal
 * @param lines the number of lines to scroll down.
 */
static void termScrollDown(NS(Terminal) *this, size_t lines) {
    for (int32_t row = 0; row < vga(getHeight)() - 1; ++row) {
        for (int32_t col = 0; col < vga(getWidth)(); ++col) {
            vga(setChar)(row, col, vga(getChar)(row, col));
        }
    }
    for (int32_t col = 0; col < vga(getWidth)(); ++col) {
        vga(setChar)(vga(getHeight)() - 1, col, ' ');
    }
}

/**
 * Move the cursor to the beginning of next line
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
 * @param this the terminal
 */
static void termPrevLine(NS(Terminal) *this) {
    if (this->curY == 0) {
        this->curX = 0;
    } else {
        --this->curY;
        this->curX = vga(getWidth)() - 1;
    }
}

void NS(termPutChar)(NS(Terminal) *this, char ch) {
    if (ch == '\n') {
        termNextLine(this);
    } else if (ch == '\b') {
        // move back the cursor, then put a ' '
        if (this->curX != 0) {
            --this->curX;
        } else {
            termPrevLine(this);
        }
        vga(setChar)(this->curX, this->curY, ' ');
    } else {
        vga(setChar)(this->curX, this->curY, ch);
        ++this->curX;
        if (this->curX == this->maxWidth) {
            termNextLine(this);
        }
    }
    vga(moveCursor)(this->curX, this->curY);
}

char NS(termGetChar)(NS(Terminal) *term) {
    // If the buffer is ready
    //   return a character from the buffer
    // Else: wait and read from keyboard, until
    //   the buffer becomes ready.
}