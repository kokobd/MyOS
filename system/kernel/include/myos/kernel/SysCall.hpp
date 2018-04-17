#pragma once

#include <myos/kernel/cpu/InterruptHandler.hpp>
#include <myos/kernel/cpu/CPU.hpp>
#include <myos/kernel/cpu/RegisterState.hpp>
#include <myos/kernel/drivers/VGAScreen.hpp>

namespace myos::kernel {

namespace drivers {
class VGAScreen;
}

class Kernel;

/**
 * You should create an object of this class
 * and leave it there.
 */
class SysCall {
public:
    explicit SysCall(drivers::VGAScreen &vgaScreen);

private:

    class InterruptHandlerImpl : public cpu::InterruptHandler {
    public:
        explicit InterruptHandlerImpl(drivers::VGAScreen &vgaScreen);

        void handleInterrupt(
                cpu::InterruptType interrupt,
                cpu::RegisterState &registerState) override;

    private:
        uint32_t runSysCall(uint32_t number,
                            uint32_t arg1,
                            uint32_t arg2,
                            uint32_t arg3);

        drivers::VGAScreen &vgaScreen;
    };

    InterruptHandlerImpl handler;
};

}
