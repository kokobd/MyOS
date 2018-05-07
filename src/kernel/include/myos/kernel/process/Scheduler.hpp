#pragma once

#include <myos/kernel/filesystem/FileSystem.hpp>
#include <myos/kernel/cpu/InterruptHandler.hpp>
#include <myos/core/collections/Queue.hpp>

namespace myos::kernel::ram {
class PageFrameManager;
}

namespace myos::kernel::process {

class Process;

class Scheduler {
private:
    class ClockInterruptHandler : public cpu::InterruptHandler {
    public:
        explicit ClockInterruptHandler(Scheduler &scheduler)
                : scheduler(scheduler) {}

        void handleInterrupt(cpu::InterruptType interrupt, cpu::RegisterState &registerState) override;

    private:
        Scheduler &scheduler;
    };

public:
    explicit Scheduler();

    void spawnProcess(Process *newProcess);

    ~Scheduler();

private:
    Process *running;
    myos::core::collections::Queue<Process *> ready;

    ClockInterruptHandler clockInterruptHandler;
};

}
