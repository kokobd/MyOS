#include <myos/kernel/Kernel.hpp>
#include <myos/kernel/process/Process.hpp>

namespace myos::kernel {

Kernel Kernel::currentKernel;

Kernel::Kernel()
        : fileSystem(floppy),
          sysCall(vgaScreen) {
//    using process::Process;
//    scheduler.spawnProcess(new Process("SPIN.EXE"));
//    scheduler.spawnProcess(new Process("KSAPP.EXE"));
    vgaScreen.setChar(0, 0, 'A');
}

Kernel &Kernel::getCurrentKernel() {
    return currentKernel;
}

bool Kernel::isRunning() {
    return true;
}

}

extern "C" void __cxa_pure_virtual() {
    // No op
}

namespace {

class Int {
public:
    Int() {
        asm volatile("nop");
    }
};

// So that we can make sure .init_array section exists.
Int dumb;

}

extern "C" uint32_t __init_array_start;

extern "C" {

int c_main() {
    extern int main();
    auto ctor = reinterpret_cast<void (*)()>(__init_array_start);
    ctor();
    return main();
}

void *__dso_handle;

int __cxa_atexit(void (*destructor)(void *), void *arg, void *dso) {
    return 0;
}

void __cxa_finalize(void *f) {

}

}
