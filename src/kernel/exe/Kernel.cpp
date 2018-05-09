#include <myos/kernel/Kernel.hpp>
#include <myos/kernel/process/Process.hpp>

namespace myos::kernel {

Kernel Kernel::currentKernel;

Kernel::Kernel() {
}

Kernel &Kernel::getCurrentKernel() {
    return currentKernel;
}

}

