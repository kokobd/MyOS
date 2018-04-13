#pragma once

#include <cstddef>
#include <cstdint>
#include "Heap.hpp"
namespace myos::kernel::ram {

class Memory {
public:
    Memory();

    Heap &getHeap() { return kernelHeap; }

private:
    void *kernelBegin;
    void *kernelEnd;
    Heap kernelHeap;
};

}
