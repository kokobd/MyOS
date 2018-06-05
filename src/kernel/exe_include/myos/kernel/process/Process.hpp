#pragma once

#include <myos/core/memory/smart_pointers/unique_ptr.hpp>
#include <myos/core/collections/BitSet.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/ram/IPageTable.hpp>
#include <myos/kernel/ram/Intel386PageTable.hpp>

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
     * @param imageAddress
     */
    explicit Process(const char *imageAddress, ram::PageManager &pageManager);

    /**
     * Copy a process. This will automatically employ copy-on-write
     * strategy.
     * @param that the process to copy from
     */
    Process(const Process &that);

    ~Process();

    const cpu::RegisterState &getRegisterState() const {
        return registerState;
    }

    void setRegisterState(const cpu::RegisterState &registerState) {
        this->registerState = registerState;
    }

private:
    cpu::RegisterState registerState;

    unique_ptr<ram::IPageTable<PageTable>> pageTable;
    // Physical address to the page frames in use by this process.
    core::collections::BitSet occupiedPages;

    ram::PageManager &pageManager;
};

}