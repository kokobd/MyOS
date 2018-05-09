#pragma once

#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/SysCall.hpp>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/process/Scheduler.hpp>

namespace myos::kernel {

class Kernel {
public:
    /**
     * Starts a kernel, if there is not an existing one.
     */
    Kernel();

    cpu::CPU &getCPU() { return cpu; }

    ram::Memory &getMemory() { return memory; }

private:
    cpu::CPU cpu;
    ram::Memory memory;

    SysCall sysCall;

    process::Scheduler scheduler;

public:
    /**
     * You may call this function only when there is a running Kernel,
     * otherwise, you are on the train of undefined behavior.
     * @return A reference to the currently running Kernel
     */
    static Kernel &getCurrentKernel();

private:
    static Kernel currentKernel;

};

}
