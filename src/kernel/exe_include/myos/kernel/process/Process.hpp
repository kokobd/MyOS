#pragma once

#include <myos/core/collections/Stack.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/ram/IPageTable.hpp>
#include <myos/kernel/ram/Intel386PageTable.hpp>

namespace myos::kernel::process {

class Process {
public:
    /**
     * Construct one of the initial processes which are typically
     * loaded into memory by bootloader.
     * @param imageAddress
     */
    explicit Process(const char *imageAddress);

    /**
     * Copy a process. This will automatically employ copy-on-write
     * strategy.
     * @param that the process to copy from
     */
    Process(const Process &that);

    const cpu::RegisterState &getRegisterState() const {
        return registerState;
    }

    void setRegisterState(const cpu::RegisterState &registerState) {
        this->registerState = registerState;
    }

private:
    cpu::RegisterState registerState;

    ram::IPageTable<ram::Intel386PageTable> pageTable;
    // Physical address to the page frames in use by this process.
    // TODO we need an efficient hash table implementation.
    core::collections::Stack<void *> occupiedPages;
};

}