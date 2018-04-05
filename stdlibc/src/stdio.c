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

size_t getFileSize(const char *fileName) {
    int32_t fileHandle = syscall(0, (int32_t) fileName, 0, 0);
    size_t fileSize = (size_t) syscall(5, fileHandle, 0, 0);
    return fileSize;
}

const char *getArgs() {
    return (const char *) syscall(6, 0, 0, 0);
}
