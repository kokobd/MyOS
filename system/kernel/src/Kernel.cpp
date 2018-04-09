#include <myos/kernel/Kernel.hpp>

namespace myos::kernel {

Kernel *Kernel::currentKernel = nullptr;

Kernel::Kernel() : sysCall(*this) {
    if (currentKernel == nullptr) {
        heap = reinterpret_cast<uint8_t *>(0x120000);

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
