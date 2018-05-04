#include <myos/kernel/Kernel.hpp>

using myos::kernel::Kernel;
using namespace myos::kernel;

extern "C" void cpu_enterUserCode(uint32_t, uint32_t);

int main() {
    Kernel &kernel = Kernel::getCurrentKernel();

    return 0;
}
