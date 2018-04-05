#include "syscall.h"
#include "../hal/idt.h"
#include "../hal/gdt.h"
#include "../filesystem/file.h"
#include "../shell.h"

#define NAMESPACE(X) kernel_syscall_ ## X

static void syscallHandler();

static int32_t syscall(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);

void NAMESPACE(initialize)() {
    idtSetHandler(0x80, 0, kernelCodeSelector(), syscallHandler);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"

static void syscallHandler() {
    register int32_t eax asm("eax");
    register int32_t ebx asm("ebx");
    register int32_t ecx asm("ecx");
    register int32_t edx asm("edx");

    int32_t ret = syscall(eax, ebx, ecx, edx);

    returnFromInterruptHandler(ret);
}

#pragma clang diagnostic pop

static int32_t syscall(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) {
    int32_t ret = -1;
    switch (arg0) {
        case 0:
            ret = kernel_filesystem_file_fopen((const char *) arg1, (uint32_t) arg2);
            break;
        case 1:
            ret = kernel_filesystem_file_fclose(arg1);
            break;
        case 2:
            ret = kernel_filesystem_file_fread(arg1, (uint8_t *) arg2, (size_t) arg3);
            break;
        case 3:
            kernel_shell_termPutChar(kernel_shell_getGlobalTerminal(), (char) arg1);
            ret = 0;
            break;
        case 4:
            ret = kernel_shell_termGetChar(kernel_shell_getGlobalTerminal());
            break;
        case 5:
            ret = kernel_filesystem_file_fGetSize(arg1);
            break;
        case 6:
            ret = (int32_t) kernel_shell_getGlobalTerminal()->arg;
        default:
            break;
    }
    return ret;
}
