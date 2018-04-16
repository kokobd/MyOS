#pragma once

#include <cstddef>
#include <cstdint>

namespace myos::kernel::common {

class BitSet {
public:
    explicit BitSet(size_t length);

    ~BitSet() { delete[] data; }

    void set(size_t index, bool on = true);

    size_t findFirst(bool on = true);

private:
    uint32_t *data;

    size_t length;

    size_t sizeInUInt32;
};

}
