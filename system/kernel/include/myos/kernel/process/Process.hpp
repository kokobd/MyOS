#pragma once

#include <myos/kernel/common/Stack.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/ram/VirtualMemoryMapping.hpp>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/filesystem/FileSystem.hpp>

namespace myos::kernel::process {

class Process {
public:
    explicit Process(const char *fileName);

    const cpu::RegisterState &getRegisterState() const {
        return registerState;
    }

    void switchVirtualMemory();

private:
    cpu::RegisterState registerState;
    common::Stack<void *> pageFrames;
    ram::VirtualMemoryMapping virtualMemoryMapping;

    void loadELF32Image(const char *fileName);

    void setupStack();
};

}