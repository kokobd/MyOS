#pragma once

#include <myos/kernel/cpu/InterruptHandler.hpp>
#include <myos/core/collections/Queue.hpp>
#include <myos/core/memory/smart_pointers/unique_ptr.hpp>

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

    template<typename T>
    using unique_ptr = core::memory::smart_pointers::unique_ptr<T>;

public:
    explicit Scheduler();

    void spawnProcess(unique_ptr<Process> &&newProcess);

    void dispatch();

private:

    unique_ptr<Process> running;
    myos::core::collections::Queue<unique_ptr<Process>> ready;

    ClockInterruptHandler clockInterruptHandler;
};

}
