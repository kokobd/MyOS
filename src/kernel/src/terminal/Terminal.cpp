#include <myos/kernel/terminal/Terminal.hpp>
#include "../screen/vga.h"

namespace myos::kernel::drivers::terminal {

Terminal::Terminal(VGAScreen &screen)
        : screen(screen),
          curX(0), curY(0),
          maxWidth(kernel_screen_vga_getWidth()),
          maxHeight(kernel_screen_vga_getHeight()),
          inputBufferReady(false) {
}

void Terminal::putChar(char ch) {
    if (ch == '\n') {
//        gotoNextLine();
    } else if (ch == '\b') {
        // move back the cursor, then put a ' '
//        gotoPrevChar();
        screen.setChar(curY, curX, ' ');
    } else {
        screen.setChar(curY, curX, ch);
//        gotoNextChar();
    }
    screen.moveCursor(curY, curX);
}

void Terminal::putString(const char *c_str) {

}

char Terminal::getChar() {
    return 0;
}

}

