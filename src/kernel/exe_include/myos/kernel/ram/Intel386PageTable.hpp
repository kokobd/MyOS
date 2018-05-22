#pragma once

#include <myos/kernel/ram/IPageTable.hpp>
#include <cstdint>

namespace myos::kernel::ram {

static_assert(sizeof(void *) == sizeof(uint32_t),
              "This class only works for 32 bit x86 arch.");

class Intel386PageTable : public IPageTable<Intel386PageTable> {
public:
    explicit Intel386PageTable(uintptr_t maxAddress);

    static constexpr size_t pageSize_impl() {
        return 4096;
    }

    static constexpr size_t pageShift_impl() {
        return 12;
    }

    bool setPageAddress_impl(void *vaddr, void *paddr);

    bool setPageFlags_impl(void *vaddr, Flags flags);

    void *getPage_impl(void *vaddr, Flags &flags);

    void installToCPU_impl() const;

    ~Intel386PageTable() override;

private:
    struct PageDirectoryEntry {
        bool present:1;
        bool writable:1;
        bool userMode:1;
        bool writeThrough:1;
        bool cacheDisabled:1;
        bool accessed:1;
        bool reserved:1;
        bool pageSize:1; // 1: 4MB. 0: 4KB
        bool globalPage:1;
        uint8_t avail:3;
        uint32_t pageTableAddress:20;
    };

    struct PageTableEntry {
        bool present:1;
        bool writable:1;
        bool userMode:1;
        bool writeThrough:1;
        bool cacheDisabled:1;
        bool accessed:1;
        bool dirty:1;
        bool reserved:1;
        bool global:1;
        uint8_t avail:3;
        uint32_t frameAddress:20;
    };

    PageDirectoryEntry *pageDirectoryTable;
    PageTableEntry *pageTable;
    uint8_t *storage;

    uintptr_t maxAddress;

private:
    PageTableEntry &getEntryByAddress(void *vaddr);

    bool checkVirtualAddress(void *vaddr);

    mutable bool pagingEnabled;

    void enablePaging() const;
};

}
