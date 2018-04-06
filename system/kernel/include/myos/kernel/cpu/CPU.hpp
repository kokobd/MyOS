#pragma once

#include "GDT.hpp"

namespace myos::kernel::cpu {

class CPU {
public:
    CPU();

private:
    GDT<16> gdt;
};

}
