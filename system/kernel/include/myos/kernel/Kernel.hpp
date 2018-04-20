#pragma once

#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/SysCall.hpp>
#include <myos/kernel/ram/Memory.hpp>
#include <myos/kernel/drivers/VGAScreen.hpp>
#include <myos/kernel/drivers/Floppy.hpp>
#include <myos/kernel/filesystem/FileSystem.hpp>
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

    filesystem::FileSystem &getFileSystem() { return fileSystem; }

private:
    cpu::CPU cpu;
    ram::Memory memory;

    drivers::VGAScreen vgaScreen;
    drivers::Floppy floppy;
    filesystem::FileSystem fileSystem;
    SysCall sysCall;

    process::Scheduler scheduler;

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
    static Kernel currentKernel;

};

}
