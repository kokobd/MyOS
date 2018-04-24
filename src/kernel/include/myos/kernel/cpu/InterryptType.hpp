#pragma once

namespace myos::kernel::cpu {

enum class InterruptType {
    // CPU
    DIVISION_ERROR, // 0x0
    GENERAL_PROTECTION_FAULT, // 0xD
    PAGE_FAULT, // 0xE

    // External Hardware
    // We will map IRQ0 ~ IRQ15 to 0x20 ~ 0x2F
    TIMER, //  0x20
    KEYBOARD, // 0x21
    FLOPPY, // 0x26

    // Software
    SYSTEM_CALL // 0x80
};

}
