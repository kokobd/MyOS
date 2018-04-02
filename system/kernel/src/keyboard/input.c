#include <stdlib.h>
#include <stdbool.h>
#include "input.h"
#include "../hal/io.h"
#include "scanCode.h"
#include "key.h"

#define NS(X) kernel_keyboard_input_ ## X

static void waitUntilReadyForInput() {
    bool hasInput = false;
    while (!hasInput) {
        uint8_t status = inb(0x64);
        hasInput = (status & 0x01) == 0x01;
    }
}

static void waitUntilReadyForOutput() {
    bool canOutput = false;
    while (!canOutput) {
        uint8_t status = inb(0x64);
        canOutput = (status & 0x02) == 0;
    }
}

int32_t NS(initialize)() {
    // Disable codeset translation,
    // so that we will use codeset 2
    waitUntilReadyForOutput();
    outb(0x64, 0x60);
    waitUntilReadyForOutput();
    outb(0x64, 0b00000100);
    waitUntilReadyForOutput();
}

static uint8_t getScanCode() {
    waitUntilReadyForInput();
    uint8_t code = inb(0x60);
    return code;
}

char NS(getChar)() {
    uint8_t code = getScanCode();
    kernel_keyboard_key_Key key = kernel_keyboard_scanCode_toKey(code);
    if (!key.pressed) {
        return -1;
    }
    if (key.keyCode > 0)
        return (char) key.keyCode;
}
