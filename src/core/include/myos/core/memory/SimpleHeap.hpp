#pragma once

#include <cstdint>
#include "Heap.hpp"

namespace myos::core::memory {

class SimpleHeap : public Heap {
public:
    SimpleHeap(void *begin, size_t size);

    void *allocate(size_t size) override;

    void deallocate(void *pt) override;

private:
#ifdef __i386__
#pragma pack(push, 4)
#else
#pragma pack(push, 8)
#endif
    struct BlockHeader {
        BlockHeader *next;
        BlockHeader *prev;
        size_t size;
        bool occupied;
    };
#pragma pack(pop)

    BlockHeader *firstBlock;

    void tryMergeBlockWithNext(BlockHeader *block);
};

}
