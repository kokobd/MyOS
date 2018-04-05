#pragma once

#pragma push_macro("NS")
#define NS(X) kernel_keyboard_key_ ## X

typedef struct {
    int8_t keyCode;
    bool pressed;
} NS(Key);

#pragma pop_macro("NS")
