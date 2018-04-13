#pragma once

#include <cstdint>

namespace myos::kernel::cpu {

#pragma pack(push, 4)
struct RegisterState {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;

    uint16_t ds;
    uint16_t null0;
    uint16_t es;
    uint16_t null1;
    uint16_t fs;
    uint16_t null2;
    uint16_t gs;
    uint16_t null3;

    uint32_t errorCode;
    uint32_t eip;
    uint16_t cs;
    uint16_t null4;
    uint32_t eflags;
    uint32_t esp;
    uint16_t ss;
    uint16_t null5;
};
#pragma pack(pop)

}


