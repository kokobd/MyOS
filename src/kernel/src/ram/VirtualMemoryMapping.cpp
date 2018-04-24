#include <myos/kernel/ram/VirtualMemoryMapping.hpp>
#include <cstring>

namespace myos::kernel::ram {

VirtualMemoryMapping::VirtualMemoryMapping() {
    // we allocate:
    //   - 4KiB for page directory table
    //   - 4KiB * 2 for two page table
    //   - 4KiB, so that we can align tables to 4KiB
    memory = new uint8_t[4096 * (1 + 2 + 1)];
    pageDirectoryTable = reinterpret_cast<PageDirectoryEntry *>(
            ((reinterpret_cast<uintptr_t>(memory) >> 12u) + 1) << 12u );
    pageTable = reinterpret_cast<PageTableEntry *>(
            reinterpret_cast<uint8_t *>(pageDirectoryTable) + 4096);
    memset(pageDirectoryTable, 0, 4096);
    for (int i = 0; i < 2; ++i) {
        pageDirectoryTable[i].present = true;
        pageDirectoryTable[i].writable = true;
        pageDirectoryTable[i].userMode = i == 1;
        pageDirectoryTable[i].writeThrough = false;
        pageDirectoryTable[i].cacheDisabled = false;
        pageDirectoryTable[i].pageSize = false;
        pageDirectoryTable[i].globalPage = false;
        pageDirectoryTable[i].pageTableAddress =
                (reinterpret_cast<uint32_t>(pageTable) >> 12) + i;
    }
    memset(pageTable, 0, 4096 * 2);
    for (uint32_t i = 0; i < 2048; ++i) {
        pageTable[i].present = true;
        pageTable[i].writable = true;
        pageTable[i].userMode = i >= 1024;
        pageTable[i].writeThrough = false;
        pageTable[i].cacheDisabled = false;
        pageTable[i].global = false;
        pageTable[i].frameAddress = i;
    }
}

bool VirtualMemoryMapping::set(void *address, void *pageFrame) {
    uint32_t source_ = reinterpret_cast<uint32_t>(address) >> 12;
    uint32_t target_ = reinterpret_cast<uint32_t>(pageFrame) >> 12;
    if (source_ >= 2048) {
        return false;
    }
    pageTable[source_].frameAddress = target_;

    return true;
}

VirtualMemoryMapping::~VirtualMemoryMapping() {
    delete[] memory;
}

void VirtualMemoryMapping::install() {
    asm volatile (
    "mov cr3, %0\n"
    : : "r" (pageDirectoryTable)
    );
}

void VirtualMemoryMapping::enablePaging() {
    asm volatile (
    "mov eax, cr0\n"
    "or eax, 0x80000000\n"
    "mov cr0, eax\n"
    : : : "eax"
    );
}

}
