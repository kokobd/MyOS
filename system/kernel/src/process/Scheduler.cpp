#include <myos/kernel/process/Scheduler.hpp>
#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/ram/PageFrameManager.hpp>

namespace myos::kernel::process {

Scheduler::Scheduler(ram::PageFrameManager &pageFrameManager)
        : running(nullptr), pageFrameManager(pageFrameManager) {

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

}
