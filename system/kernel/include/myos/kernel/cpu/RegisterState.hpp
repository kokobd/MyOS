#pragma once

namespace myos::kernel::cpu {

struct RegisterState {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;

    RegisterState(uint32_t eax = 0, uint32_t ebx = 0, uint32_t ecx = 0, uint32_t edx = 0, uint32_t esi = 0,
                  uint32_t edi = 0)
            : eax(eax), ebx(ebx), ecx(ecx), edx(edx), esi(esi), edi(edi) {}
};

}
