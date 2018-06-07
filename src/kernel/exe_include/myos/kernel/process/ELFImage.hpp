#pragma once

#include <cstdint>
#include <cstddef>
#include <myos/kernel/process/ELFProgramHeader.hpp>

namespace myos::kernel::process {

class ELFImage {
public:
    ELFImage(uintptr_t startAddress) : startAddress(startAddress) {}

    const ELFProgramHeader *programHeaders() const;

    uint16_t programHeadersCount() const;

    uintptr_t entryPoint() const;

    size_t sizeInMemory() const;

    bool isValid() const;

    /**
     * Load this ELF image with check on boundary.
     * Only addresses within [min, max) are valid.
     */
    bool loadWithCheck(uintptr_t min, uintptr_t max) const;

private:
    uintptr_t startAddress;
};

}
