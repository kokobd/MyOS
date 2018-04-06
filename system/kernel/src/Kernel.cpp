#include <myos/kernel/Kernel.hpp>

namespace myos::kernel {

Kernel *Kernel::currentKernel = nullptr;

Kernel::Kernel() {
    if (currentKernel == nullptr) {
        // TODO Do necessary initialization
        currentKernel = this;
    }
}

Kernel::~Kernel() {
    currentKernel = nullptr;
}

Kernel &Kernel::getCurrentKernel() {
    return *currentKernel;
}

bool Kernel::isRunning() {
    return currentKernel != nullptr;
}

}
