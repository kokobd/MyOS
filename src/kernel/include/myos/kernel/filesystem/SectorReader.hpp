#pragma once
#include <cstdint>

namespace myos::kernel::filesystem {

class SectorReader {
public:
    virtual bool readSector(uint8_t *buffer, uint32_t index) = 0;

    size_t sectorSize() const {
        return sector_size;
    }

protected:
    void setSectorSize(size_t sector_size) {
        this->sector_size = sector_size;
    }

private:
    size_t sector_size = 0;
};

}
