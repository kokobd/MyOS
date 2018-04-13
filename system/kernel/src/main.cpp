#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cctype>

#include <myos/kernel/Kernel.hpp>
#include "keyboard/input.h"
#include "shell.h"
#include "filesystem/file.h"
#include "exec/elf32.h"
// TODO remove this include
#include <myos/kernel/cpu/InterruptHandler.hpp>

static void initAll();

static void executeApplication(kernel_shell_Terminal *terminal, const char *name);

using myos::kernel::Kernel;
using namespace myos::kernel;

class ClockHandler : public cpu::InterruptHandler {
public:
    explicit ClockHandler(kernel_shell_Terminal *terminal) : ch('0'), terminal(terminal) {}
    void handleInterrupt(cpu::InterruptType interrupt, cpu::RegisterState &registerState) override {
        kernel_shell_termPutChar(terminal, ch);

        if (ch == '9')
            ch = '0';
        else ++ch;
    }
private:
    char ch;
    kernel_shell_Terminal *terminal;
};

void userFunc() {
    asm volatile (
    "int 0x80\n"
    );
}

extern "C" int main() {
    Kernel kernel;
    void *userProgram = reinterpret_cast<void *>(userFunc);
    kernel.getCPU().enterUserCode(userProgram,
                                  (void *) 0x300000);

//    kernel_shell_Terminal *terminal = kernel_shell_getGlobalTerminal();
//    kernel_shell_termInit(terminal);
//    kernel_shell_termPutString(terminal, "Hello\n");
//
//    ClockHandler clockHandler(terminal);
//    kernel.getCPU().registerInterruptHandler(cpu::InterruptType::TIMER, &clockHandler);
//#pragma clang diagnostic push
//#pragma clang diagnostic ignored "-Wmissing-noreturn"
//    while (true) {
//        asm volatile ( "nop" );
//    }
//#pragma clang diagnostic pop
//
//    size_t INPUT_LIMIT = 120;
//    char input[INPUT_LIMIT];
//    memset(input, 0, INPUT_LIMIT);
//    while (strcmp(input, "EXIT") != 0) {
//        kernel_shell_termPutString(terminal, "MyOS 0.1> ");
//        memset(input, 0, INPUT_LIMIT);
//        size_t inputSize = kernel_shell_termReadLine(terminal, input, INPUT_LIMIT - 1);
//
//        const char *progNameEnd;
//        for (progNameEnd = input; *progNameEnd != '\0'; ++progNameEnd) {
//            if (isspace(*progNameEnd))
//                break;
//        }
//
//        char progName[80];
//        memset(progName, 0, 80);
//        memcpy(progName, input, progNameEnd - input);
//
//        const char *suffix = ".exe";
//        memcpy(progName + strlen(progName), suffix, strlen(suffix));
//
//        for (char *pt = progName; *pt != '\0'; ++pt) {
//            *pt = (char) toupper(*pt);
//        }
//
//        kernel_shell_termSetArg(terminal, input);
//        executeApplication(terminal, progName);
//    }
//
//    kernel_shell_termPutString(terminal, "Exited.\n");
//    asm(
//    "cli\n"
//    "hlt"
//    );
}

static void executeApplication(kernel_shell_Terminal *terminal, const char *name) {
    int32_t fileHandle = kernel_filesystem_file_fopen(name, 0);
    if (fileHandle >= 0) {
        uint8_t *image = (uint8_t *) 0x200000;
        const size_t sizeLimit = 0x100000;
        int ret = kernel_filesystem_file_fread(fileHandle, image, sizeLimit);
        kernel_exec_elf32_execute(image);
        kernel_filesystem_file_fclose(fileHandle);
    } else {
        kernel_shell_termPutString(terminal, "Can not find executable ");
        kernel_shell_termPutString(terminal, name);
        kernel_shell_termPutChar(terminal, '\n');
    }
}
