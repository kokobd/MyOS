#include <stdio.h>
#include <sys/syscall.h>

bool setChar(uint32_t row, uint32_t col, char ch) {
    return syscall(0, row, col, ch) == 0;
}
