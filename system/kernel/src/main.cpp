#include <myos/kernel/Kernel.hpp>

using myos::kernel::Kernel;
using namespace myos::kernel;

void userFunc() {
    asm volatile (
    "int 0x80\n"
    );
}

int main() {
    Kernel &kernel = Kernel::getCurrentKernel();
    void *userProgram = reinterpret_cast<void *>(userFunc);
    kernel.getCPU().enterUserCode(userProgram,
                                  (void *) 0x300000);

    return 0;
}
