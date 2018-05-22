#pragma once

#include <myos/core/collections/Stack.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/ram/IPageTable.hpp>
#include <myos/kernel/ram/Intel386PageTable.hpp>

namespace myos::kernel::process {

class Process {
public:
    explicit Process(const char *fileName);

    const cpu::RegisterState &getRegisterState() const {
        return registerState;
    }

    void setRegisterState(const cpu::RegisterState &registerState) {
        this->registerState = registerState;
    }

    void switchVirtualMemory();

private:
    cpu::RegisterState registerState;
    ram::IPageTable<ram::Intel386PageTable> pageTable;
};

}