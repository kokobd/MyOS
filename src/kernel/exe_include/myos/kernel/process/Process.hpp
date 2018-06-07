#pragma once

#include <myos/core/memory/smart_pointers/unique_ptr.hpp>
#include <myos/core/collections/BitSet.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/ram/IPageTable.hpp>
#include <myos/kernel/ram/Intel386PageTable.hpp>
#include "ELFImage.hpp"

namespace myos::kernel::ram {
class PageManager;
}

namespace myos::kernel::process {

class Process {
    template<typename T>
    using unique_ptr = core::memory::smart_pointers::unique_ptr<T>;

    using PageTable = ram::Intel386PageTable;
public:
    /**
     * Construct one of the initial processes which are typically
     * loaded into memory by bootloader.
     * Note that the process constructor may fail. You should
     * always validate the instance with its 'conversion to bool'
     * @param imageAddress
     */
    explicit Process(const uint8_t *imageAddress, ram::PageManager &pageManager);

    /**
     * Copy a process. This will automatically employ copy-on-write
     * strategy.
     * @param that the process to copy from
     */
    Process(const Process &that);

    ~Process();

    operator bool();

    /**
     * Replace the current process with a loaded image. Further execution
     * of this process starts from new image's entry.
     * @param loadedImageAddress MUST be aligned to page boundary.
     * @param loadedImageSize size of the loaded image (in bytes)
     */
    void replace(const uint8_t *loadedImageAddress, size_t loadedImageSize);

    const cpu::RegisterState &getRegisterState() const {
        return registerState;
    }

    void setRegisterState(const cpu::RegisterState &registerState) {
        this->registerState = registerState;
    }

private:
    cpu::RegisterState registerState;

    unique_ptr<ram::IPageTable<PageTable>> pageTable;
    // Physical address -->> the page frames in use by this process.
    core::collections::BitSet occupiedPages;

    ram::PageManager &pageManager;

    uintptr_t programBreak;

    bool valid;

    void allocPage(uintptr_t vaddr);

    void releasePage(uintptr_t vaddr);

    void initPages(const ELFImage &image);

    void movePage(uintptr_t from, uintptr_t to);
};

}