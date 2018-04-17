#pragma once

#include <myos/kernel/common/Stack.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/ram/VirtualMemoryMapping.hpp>

namespace myos::kernel::process {

class Process {
public:
    /**
     * Create a new process with an executable file.
     * @param file
     */
    explicit Process(const char *file);

private:
    cpu::RegisterState registerState;
    common::Stack<void *> pageFrames;
    ram::VirtualMemoryMapping virtualMemoryMapping;
};

}