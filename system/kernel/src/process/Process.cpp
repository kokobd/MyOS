#include <myos/kernel/process/Process.hpp>
#include <myos/kernel/Kernel.hpp>
#include <cstring>

using myos::kernel::ram::Memory;
using myos::kernel::ram::VirtualMemoryMapping;
using myos::kernel::filesystem::FileSystem;

namespace myos::kernel::process {

Process::Process(const char *fileName) {
    setupStack();
    loadELF32Image(fileName);
}

void Process::loadELF32Image(const char *fileName) {
    FileSystem &fileSystem = Kernel::getCurrentKernel().getFileSystem();
    Memory &memory = Kernel::getCurrentKernel().getMemory();
    uint8_t *const base = reinterpret_cast<uint8_t *const>(0x400000); // each process starts from 4MiB
    const size_t PAGE_FRAME_SIZE = ram::VirtualMemoryMapping::pageFrameSize();

    FileSystem::FileHandle file = fileSystem.openFile(fileName);

    // Allocate memory for user program code.
    size_t imageSize = fileSystem.getSize(file);
    uint8_t *vpt = base;
    while (static_cast<size_t>(vpt - base) < imageSize) {
        void *pf = memory.allocatePageFrame();
        pageFrames.push(pf);
        virtualMemoryMapping.set(vpt, pf);
        vpt += PAGE_FRAME_SIZE;
    }

    // Load ELF32 image into memory.
    virtualMemoryMapping.install();
    fileSystem.readAllBytes(file, base);
    // Of course, this breaks .data, .rodata sections.
    // For simplicity, we use this simple method now
    uint32_t entryPoint = *(reinterpret_cast<uint32_t *>(base + 0x18));
    registerState.eip = entryPoint;

    fileSystem.closeFile(file);
}

void Process::setupStack() {
    Memory &memory = Kernel::getCurrentKernel().getMemory();

    // !!LOWER!! boundary of the stack.
    uint8_t *stackBasePhysical =
            static_cast<uint8_t *>(memory.allocatePageFrame());
    pageFrames.push(stackBasePhysical);
    virtualMemoryMapping.set(
            reinterpret_cast<void *>(0x800000u
                                     - VirtualMemoryMapping::pageFrameSize()),
            stackBasePhysical);
    registerState.esp = 0x7FFFFFu;
    registerState.ebp = registerState.esp;

}

void Process::switchVirtualMemory() {
    virtualMemoryMapping.install();
}

}
