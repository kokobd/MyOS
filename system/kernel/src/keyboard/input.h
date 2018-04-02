#pragma once

#pragma push_macro("NS")
#define NS(X) kernel_keyboard_input_ ## X

int32_t NS(initialize)();

char NS(getChar)();

#pragma pop_macro("NS")
