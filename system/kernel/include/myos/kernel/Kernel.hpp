#pragma once

#include <myos/kernel/cpu/CPU.hpp>

namespace myos::kernel {

class Kernel {
public:
    /**
     * Starts a kernel, if there is not an existing one.
     */
    Kernel();

    ~Kernel();

    cpu::CPU &getCPU() { return cpu; }

private:
    cpu::CPU cpu;

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
};

}
