#include <myos/kernel/Kernel.hpp>

using myos::kernel::Kernel;
using namespace myos::kernel;

extern "C" void cpu_enterUserCode();

int main() {
    Kernel &kernel = Kernel::getCurrentKernel();
    cpu_enterUserCode();

    return 0;
}
