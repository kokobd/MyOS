#include <myos/kernel/process/ELFImage.hpp>
#include <climits>
#include <cstring>

static_assert(sizeof(uint32_t) == sizeof(uintptr_t));

namespace myos::kernel::process {

uintptr_t ELFImage::entryPoint() const {
    return *reinterpret_cast<uint32_t *>(startAddress + 0x18);
}

const ELFProgramHeader *ELFImage::programHeaders() const {
    uintptr_t phoff = *reinterpret_cast<uint32_t *>(startAddress + 0x1C);
    return reinterpret_cast<const ELFProgramHeader *>(startAddress + phoff);
}

uint16_t ELFImage::programHeadersCount() const {
    return *reinterpret_cast<uint16_t *>(startAddress + 0x2C);
}

size_t ELFImage::sizeInMemory() const {
    uintptr_t minAddress = UINTPTR_MAX;
    uintptr_t maxAddress = 0;
    for (uint16_t i = 0; i < programHeadersCount(); ++i) {
        const ELFProgramHeader &aHeader = programHeaders()[i];
        if (aHeader.type == ELFProgramHeader::PT_LOAD) {
            if (aHeader.vaddr < minAddress)
                minAddress = aHeader.vaddr;
            uintptr_t curMaxAddress = aHeader.vaddr + aHeader.memorySize - 1;
            if (curMaxAddress > maxAddress)
                maxAddress = curMaxAddress;
        }
    }
    return maxAddress - minAddress;
}

bool ELFImage::isValid() const {
    const uint8_t *startAddress_ = reinterpret_cast<const uint8_t *>(startAddress);
    uint8_t magicNumber[] = {0x7F, 0x45, 0x4C, 0x46};
    for (int i = 0; i < 4; i++) {
        if (magicNumber[i] != startAddress_[i])
            return false;
    }



    return true;
}

}
