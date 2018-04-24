
#include <myos/kernel/common/BitSet.hpp>
#include <cstring>

namespace myos::kernel::common {

BitSet::BitSet(size_t length) : length(length) {
    sizeInUInt32 = length / 32 + 1;
    data = new uint32_t[sizeInUInt32];
    memset(data, 0, sizeInUInt32 * sizeof(uint32_t));
}

void BitSet::set(size_t index, bool on) {
    if (index >= length)
        return;
    if (on) {
        data[index / 32u] |= (1u << (index % 32u));
    } else {
        data[index / 32u] &= ~(1u << (index % 32u));
    }
}

size_t BitSet::findFirst(bool on) {
    if (on) {
        for (size_t i = 0; i != sizeInUInt32; ++i) {
            if (data[i]) {
                size_t len = i * 32u;
                uint32_t mask = 1;
                while (mask != 0) {
                    if (data[i] & mask) {
                        return len;
                    }
                    ++len;
                    mask = mask << 1;
                }
                // Impossible code path
                return len;
            }
        }
    } else {
        for (size_t i = 0; i != sizeInUInt32; ++i) {
            if (~data[i]) {
                size_t len = i * 32u;
                uint32_t mask = 1;
                while (mask != 0) {
                    if (~data[i] & mask) {
                        return len;
                    }
                    ++len;
                    mask = mask << 1;
                }
                // Impossible code path
                return len;
            }
        }
    }

    return length;
}

}