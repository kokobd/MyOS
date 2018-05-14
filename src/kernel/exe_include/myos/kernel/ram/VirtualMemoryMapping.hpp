#pragma once

#include <cstdint>
#include <cstddef>
#include <myos/core/collections/Stack.hpp>

namespace myos::kernel::ram {

/**
 * Describes a virtual memory mapping.
 * Note that we can only map the lowest 8MiB memory,
 * i.e. 0x000000 to 0x7FFFFF. All higher address are
 * mapped as 'not present'.
 *
 * Before dropping a mapping, you MUST install another.
 * The only way you may change virtual memory mapping is
 * through this class. Otherwise, no behavior is guranteed.
 */
class VirtualMemoryMapping {
public:
    /**
     * Constructs an identity mapping.
     * Lower 4MiB is in supervisor mode, higher 4MiB
     * is in user mode.
     */
    VirtualMemoryMapping();

    VirtualMemoryMapping(const VirtualMemoryMapping &that);

    ~VirtualMemoryMapping();

    /**
     * Get size of a page frame.
     */
    static constexpr size_t pageFrameSize() { return 1 << 12; }

    /**
     * Maps an virtual address to a page frame.
     * Note that both parameters must be aligned to
     * the size of a page frame, and a whole page will
     * be mapped.
     * @param vaddr the virtual address
     * @param paddr the physical address
     * @return whether it succeeded.
     */
    bool set(void *vaddr, void *paddr);

    /**
     * Tells the CPU to use the current memory mapping.
     * This method will flush TLB, if necessary.
     */
    void install();

    /**
     * Enable paging. You must install one prior to calling this.
     */
    static void enablePaging();

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

    uint8_t *memory;
    PageDirectoryEntry *pageDirectoryTable;
    PageTableEntry *pageTable;

    core::collections::Stack<void *> pages;
};

}
