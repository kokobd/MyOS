#pragma once

#include <myos/kernel/cpu/InterruptHandler.hpp>
#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>

namespace myos::kernel {

class Kernel;

/**
 * You should create an object of this class
 * and leave it there.
 */
class SysCall {
public:
    /**
     * Initialize the system call module.
     * @param kernel
     */
    explicit SysCall(Kernel &kernel);

private:
    Kernel &kernel;

    class InterruptHandlerImpl : public cpu::InterruptHandler {
    public:
        explicit InterruptHandlerImpl(Kernel &kernel);

        void handleInterrupt(
                cpu::InterruptType interrupt,
                cpu::RegisterState &registerState) override;

    private:
        uint32_t runSysCall(uint32_t number,
                            uint32_t arg1,
                            uint32_t arg2,
                            uint32_t arg3);

        Kernel &kernel;
    };

    InterruptHandlerImpl handler;
};

}
