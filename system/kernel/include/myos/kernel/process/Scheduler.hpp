#pragma once

#include <myos/kernel/common/Queue.hpp>

namespace myos::kernel::ram {
class PageFrameManager;
}

namespace myos::kernel::process {

class Process;

class Scheduler {
public:
    explicit Scheduler(ram::PageFrameManager &pageFrameManager);

    ~Scheduler();

private:
    Process *running;
    common::Queue<Process *> ready;

    ram::PageFrameManager &pageFrameManager;
};

}
