#include "syscall.h"
#include "../hal/idt.h"
#include "../hal/gdt.h"
#include "file.h"

static void syscallHandler();

static int32_t syscall(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3);

void syscallInitialize() {
    idtSetHandler(0x80, 0, kernelCodeSelector(), syscallHandler);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuninitialized"

static void syscallHandler() {
    int32_t eax, ebx, ecx, edx;
    asm volatile (
    "mov %0, eax\n"
    "mov %1, ebx\n"
    "mov %2, ecx\n"
    "mov %3, edx\n"
    : "=rm" (eax), "=rm" (ebx), "=rm" (ecx), "=rm" (edx)
    : : "eax", "ebx", "ecx", "edx"
    );

    int32_t ret = syscall(eax, ebx, ecx, edx);

    returnFromInterruptHandler(ret);
}

#pragma clang diagnostic pop

static int32_t syscall(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) {
    int32_t ret = -1;
    switch (arg0) {
        case 0:
            ret = fopen((const char *) arg1, (uint32_t) arg2);
            break;
        default:
            break;
    }
    return ret;
}
