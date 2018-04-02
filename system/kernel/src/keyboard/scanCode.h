#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "key.h"

#pragma push_macro("NS")
#define NS(X) kernel_keyboard_scanCode_ ## X

kernel_keyboard_key_Key NS(toKey)(uint8_t scanCode);

#pragma pop_macro("NS")
