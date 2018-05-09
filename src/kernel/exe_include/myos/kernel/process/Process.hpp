#pragma once

#include <myos/core/collections/Stack.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/ram/VirtualMemoryMapping.hpp>
#include <myos/kernel/ram/Memory.hpp>

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
    core::collections::Stack<void *> pageFrames;
    ram::VirtualMemoryMapping virtualMemoryMapping;

    void loadELF32Image(const char *fileName);

    void setupStack();
};

}