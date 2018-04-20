#include <myos/kernel/process/Scheduler.hpp>
#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/ram/PageFrameManager.hpp>
#include <myos/kernel/cpu/CPU.hpp>

namespace myos::kernel::process {

Scheduler::Scheduler()
        : running(nullptr),
          clockInterruptHandler(*this) {
    cpu::CPU::getCurrentCPU()
            .registerInterruptHandler(cpu::InterruptType::TIMER, &clockInterruptHandler);
}

Scheduler::~Scheduler() {
    // We implement a destructor, though it probably will not run.
    delete running;
    while (!ready.empty()) {
        Process *front = ready.front();
        delete front;
        ready.popFront();
    }
}

void Scheduler::spawnProcess(Process *newProcess) {
    ready.pushBack(newProcess);
}

void Scheduler::ClockInterruptHandler::handleInterrupt(
        cpu::InterruptType interrupt,
        cpu::RegisterState &registerState) {
    if (interrupt != cpu::InterruptType::TIMER) {
        return;
    }

    if (scheduler.ready.empty()) {
        // No other processes to run.
        return;
    }

    Process *next = scheduler.ready.front();
    registerState = next->getRegisterState();
    next->switchVirtualMemory();
    if (scheduler.running != nullptr) {
        scheduler.ready.pushBack(scheduler.running);
    }
    scheduler.running = next;
    scheduler.ready.popFront();
}

}
