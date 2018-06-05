#pragma once

#include <cstdint>

namespace myos::kernel::process {

class ELFProgramHeader {
public:
    uint32_t type;
    uint32_t offset;
    uint32_t vaddr;
    uint32_t paddr;
    // size of the segment in file
    uint32_t fileSize;
    // size of the segment in memory
    uint32_t memorySize;
    uint32_t flags;
    uint32_t align;

    constexpr static uint32_t PT_NULL = 0;
    constexpr static uint32_t PT_LOAD = 1;
};

}
