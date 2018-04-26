#pragma once

#include <cstddef>
#include <cstdint>

namespace myos::base::collections {

class BitSet {
public:
    explicit BitSet(size_t length);

    ~BitSet() { delete[] data; }

    void set(size_t index, bool on = true);

    bool get(size_t index) const;

    size_t findFirst(bool on = true);

    size_t size() const {
        return length;
    }

private:
    uint32_t *data;

    size_t length;

    size_t sizeInUInt32;
};

}
