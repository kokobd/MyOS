#include <myos/kernel/process/Scheduler.hpp>
#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/cpu/CPU.hpp>
#include <myos/core/utility.hpp>

using myos::core::utility::move;

namespace myos::kernel::process {

Scheduler::Scheduler()
        : running(nullptr),
          clockInterruptHandler(*this) {
    cpu::CPU::getCurrentCPU()
            .registerInterruptHandler(cpu::InterruptType::TIMER, &clockInterruptHandler);
}

void Scheduler::spawnProcess(Scheduler::unique_ptr<myos::kernel::process::Process> &&newProcess) {
    ready.pushBack(move(newProcess));
}

void Scheduler::dispatch() {
    // TODO
}

void Scheduler::ClockInterruptHandler::handleInterrupt(
        cpu::InterruptType interrupt,
        cpu::RegisterState &registerState) {
    if (interrupt != cpu::InterruptType::TIMER) {
        return;
    }

    scheduler.dispatch();
}

}
