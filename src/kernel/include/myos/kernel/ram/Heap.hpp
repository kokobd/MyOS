#pragma once

#include <cstddef>
#include <cstdint>

namespace myos::kernel::ram {

/**
 * Manages a heap
 */
class Heap {
public:
    explicit Heap(void *start, size_t maxSize = SIZE_MAX);

    void *allocate(size_t size);

    void deallocate(void *pt);

private:
#pragma pack(push, 4)
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
