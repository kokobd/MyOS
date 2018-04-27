#pragma once

#include <cstddef>

namespace myos::base::memory {

class Heap {
public:
    virtual void *allocate(size_t size) = 0;

    virtual void deallocate(void *pt) = 0;
};

}