#pragma once

#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/SysCall.hpp>
#include <myos/kernel/ram/Memory.hpp>

namespace myos::kernel {

class Kernel {
public:
    /**
     * Starts a kernel, if there is not an existing one.
     */
    Kernel();

    ~Kernel();

    cpu::CPU &getCPU() { return cpu; }

    ram::Memory &getMemory() { return memory; }

private:
    cpu::CPU cpu;
    ram::Memory memory;

public:
    /**
     * You may call this function only when there is a running Kernel,
     * otherwise, you are on the train of undefined behavior.
     * @return A reference to the currently running Kernel
     */
    static Kernel &getCurrentKernel();

    /**
     * Determine if there exists a running Kernel.
     * @return true if there is
     */
    static bool isRunning();

private:
    static Kernel *currentKernel;

    uint8_t *heap;

    SysCall sysCall;
};

}
