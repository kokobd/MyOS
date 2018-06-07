#include <myos/kernel/ram/Intel386PageTable.hpp>
#include <cstring>

namespace myos::kernel::ram {

#define CHECK_VADDR(VADDR, RET) \
do {\
    if (!checkVirtualAddress((VADDR))) {\
        return RET;\
    }\
} while(false)\


bool Intel386PageTable::setPageAddress_impl(
        uintptr_t vaddr, uintptr_t paddr) {
    CHECK_VADDR(vaddr, false);
    uintptr_t paddr_ = reinterpret_cast<uintptr_t>(paddr);

    PageTableEntry &entry = getEntryByAddress(vaddr);
    entry.frameAddress =
            paddr_ >> IPageTable<Intel386PageTable>::pageShift();
    return true;
}

bool Intel386PageTable::setPageFlags_impl(
        uintptr_t vaddr,
        IPageTable<Intel386PageTable>::Flags flags) {
    CHECK_VADDR(vaddr, false);
    PageTableEntry &entry = getEntryByAddress(vaddr);
    entry.userMode = !(flags & Flags::KERNEL);
    entry.writable = flags & Flags::WRITABLE;
    entry.present = flags & Flags::PRESENT;
    return true;
}

Intel386PageTable::Intel386PageTable(uintptr_t maxAddress)
        : maxAddress(maxAddress), pagingEnabled(false) {
    // TODO actually use 'maxAddress', rather than assuming it is 0x7FFFFF (8MiB)

    // we allocate:
    //   - 4KiB for page directory table
    //   - 4KiB * 2 for two page table
    //   - 4KiB, so that we can align tables to 4KiB
    setupStorage();
    memset(pageDirectoryTable, 0, 4096);
    for (int i = 0; i < 2; ++i) {
        pageDirectoryTable[i].present = true;
        pageDirectoryTable[i].writable = true;
        pageDirectoryTable[i].userMode = false;
        pageDirectoryTable[i].writeThrough = false;
        pageDirectoryTable[i].cacheDisabled = false;
        pageDirectoryTable[i].pageSize = false;
        pageDirectoryTable[i].globalPage = false;
        pageDirectoryTable[i].pageTableAddress =
                (reinterpret_cast<uint32_t>(pageTable) >> 12u) + i;
    }
    memset(pageTable, 0, 4096 * 2);
    for (uint32_t i = 0; i < 2048; ++i) {
        pageTable[i].present = false;
        pageTable[i].writable = true;
        pageTable[i].userMode = false;
        pageTable[i].writeThrough = false;
        pageTable[i].cacheDisabled = false;
        pageTable[i].global = false;
        pageTable[i].frameAddress = i;
    }
}

uintptr_t Intel386PageTable::getPage_impl(
        uintptr_t vaddr,
        IPageTable<Intel386PageTable>::Flags &flags) {
    CHECK_VADDR(vaddr, 0);

    PageTableEntry &entry = getEntryByAddress(vaddr);
    int flags_ = 0;
    if (entry.writable)
        flags_ |= Flags::WRITABLE;
    if (!entry.userMode)
        flags_ |= Flags::KERNEL;
    flags = static_cast<Flags>(flags_);

    return entry.frameAddress << IPageTable<Intel386PageTable>::pageShift();
}

Intel386PageTable::PageTableEntry &Intel386PageTable::getEntryByAddress(uintptr_t vaddr) {
    return pageTable[reinterpret_cast<uintptr_t>(vaddr) >> IPageTable<Intel386PageTable>::pageShift()];
}

bool Intel386PageTable::checkVirtualAddress(uintptr_t vaddr) {
    return reinterpret_cast<uintptr_t>(vaddr) <= maxAddress;
}

void Intel386PageTable::installToCPU_impl() const {
    if (!pagingEnabled) {
        enablePaging();
    }
    asm volatile (
    "mov cr3, %0\n"
    : : "r" (pageDirectoryTable)
    );
}

Intel386PageTable::~Intel386PageTable() {
    delete storage;
}

void Intel386PageTable::enablePaging() const {
    asm volatile (
    "mov eax, cr0\n"
    "or eax, 0x80000000\n"
    "mov cr0, eax\n"
    : : : "eax"
    );
    pagingEnabled = true;
}

Intel386PageTable::Intel386PageTable(const Intel386PageTable &that) {
    setupStorage();
    memcpy(pageDirectoryTable, that.pageDirectoryTable, 4096);
    memcpy(pageTable, that.pageTable, 4096 * 2);
}

void Intel386PageTable::setupStorage() {
    storage = new uint8_t[4096 * (1 + 2 + 1)];
    pageDirectoryTable = reinterpret_cast<PageDirectoryEntry *>(
            ((reinterpret_cast<uintptr_t>(storage) >> 12u) + 1) << 12u );
    pageTable = reinterpret_cast<PageTableEntry *>(
            reinterpret_cast<uint8_t *>(pageDirectoryTable) + 4096);
}

}
