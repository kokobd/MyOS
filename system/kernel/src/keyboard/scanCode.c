#include "scanCode.h"

#define NS(X) kernel_keyboard_scanCode_ ## X

#define CODE_SET_SIZE 256

// index represents the scan code
static kernel_keyboard_key_Key codeSet2[CODE_SET_SIZE] = {
        // TODO implement codeset 2
        // dumb table for now
        {.keyCode = 'A', .pressed = true},
        {'a', false}
};

kernel_keyboard_key_Key NS(toKey)(uint8_t scanCode) {
    return codeSet2[scanCode];
}
