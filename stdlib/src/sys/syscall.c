#include <sys/syscall.h>

int32_t syscall(int32_t arg0, int32_t arg1, int32_t arg2, int32_t arg3) {
    asm volatile(
    "int 0x80\n"
    : : "a" (arg0), "b" (arg1), "c" (arg2), "d" (arg3)
    );
    int32_t ret;
    asm volatile(
    "mov %0, eax\n"
    : "=r" (ret)
    : : "eax"
    );
    return ret;
}
