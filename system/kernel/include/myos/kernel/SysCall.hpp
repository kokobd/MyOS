#pragma once

#include <myos/kernel/cpu/InterruptHandler.hpp>

namespace myos::kernel {

class Kernel;

class SysCall {
public:
    explicit SysCall(Kernel &kernel);

private:
    Kernel &kernel;

    class InterruptHandlerImpl : public cpu::InterruptHandler {
    public:
        explicit InterruptHandlerImpl(Kernel &kernel);
        void handleInterrupt(
                cpu::InterruptType interrupt,
                const cpu::RegisterState &registerState) override;

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
