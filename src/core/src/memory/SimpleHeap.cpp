#include <myos/core/memory/SimpleHeap.hpp>
#include <myos/core/memory.hpp>

namespace myos::core::memory {

SimpleHeap::SimpleHeap(void *begin, size_t size) {
    firstBlock = reinterpret_cast<BlockHeader *>(
            alignUpWord(begin));
    firstBlock->prev = nullptr;
    firstBlock->next = nullptr;
    firstBlock->size = reinterpret_cast<uintptr_t>(begin)
                       + size - reinterpret_cast<uintptr_t>(firstBlock);
    firstBlock->occupied = false;
}

void *SimpleHeap::allocate(size_t size) {
    size = alignUpWord(size);

    BlockHeader *pt = firstBlock;
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
            return reinterpret_cast<uint8_t *>(pt) + sizeof(BlockHeader);
        }
        pt = pt->next;
    }

    // We have exhausted all blocks, but still can not
    // find a block to use
    return nullptr;
}

void SimpleHeap::deallocate(void *pt) {
    if (pt) {
        BlockHeader *block = reinterpret_cast<BlockHeader *>(
                reinterpret_cast<uint8_t *>(pt) - sizeof(BlockHeader)
        );
        block->occupied = false;

        tryMergeBlockWithNext(block);
        tryMergeBlockWithNext(block->prev);
    }
}

void SimpleHeap::tryMergeBlockWithNext(SimpleHeap::BlockHeader *block) {
    if (block != nullptr
        && block->next != nullptr
        && !block->next->occupied) {
        block->size += sizeof(BlockHeader) + block->next->size;
        block->next = block->next->next;
        if (block->next != nullptr) {
            block->next->prev = block;
        }
    }
}

}
