#include <stdio.h>
#include <sys/syscall.h>

int putchar(int ch) {
    return syscall(3, ch, 0, 0);
}

int getchar() {
    return syscall(4, 0, 0, 0);
}

int puts(const char *str) {
    while (*str != '\0')
        putchar(*str++);
    return 0;
}
