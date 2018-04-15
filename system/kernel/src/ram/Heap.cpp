#include <myos/kernel/ram/Heap.hpp>

namespace myos::kernel::ram {

template<typename T>
inline T align4(T x) {
    uint8_t *pt = reinterpret_cast<uint8_t *>(x);
    uintptr_t ret = (reinterpret_cast<uintptr_t>(pt - 1) >> 2) << 2 + 4;
    return reinterpret_cast<T>(ret);
}

Heap::Heap(void *start, size_t maxSize) {
    firstBlock = reinterpret_cast<BlockHeader *>(
            align4(start));
    firstBlock->prev = nullptr;
    firstBlock->next = nullptr;
    firstBlock->size = maxSize;
    firstBlock->occupied = false;
}

void *Heap::allocate(size_t size) {
    size = align4(size);

    BlockHeader *&pt = firstBlock;
    while (pt != nullptr) {
        if (!pt->occupied && pt->size > size + sizeof(BlockHeader)) {
            // If there is enough room, split the block
            // 32 is an arbitrarily selected number.
            if (pt->size > size + sizeof(BlockHeader) + 32) {
                BlockHeader *newBlock = pt + sizeof(BlockHeader) + size;
                newBlock->prev = pt;
                newBlock->next = pt->next;
                newBlock->size = pt->size - size - sizeof(BlockHeader);
                newBlock->occupied = false;
                pt->next = newBlock;
            }

            pt->occupied = true;
            pt->size = size;
            return pt + sizeof(BlockHeader);
        }
        pt = pt->next;
    }
}

void Heap::deallocate(void *pt) {
    BlockHeader *block = reinterpret_cast<BlockHeader *>(
            reinterpret_cast<uint8_t *>(pt) - sizeof(BlockHeader)
    );
    block->occupied = false;

    tryMergeBlockWithNext(block);
    tryMergeBlockWithNext(block->prev);
}

void Heap::tryMergeBlockWithNext(BlockHeader *block) {
    if (block->next != nullptr && !block->next->occupied) {
        block->size += sizeof(BlockHeader) + block->next->size;
        block->next = block->next->next;
        if (block->next != nullptr) {
            block->next->prev = block;
        }
    }
}

}
