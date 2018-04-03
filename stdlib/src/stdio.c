#include <stdio.h>

int putchar(int ch) {
    // TODO
}

int getchar() {
    // TODO
}

int puts(const char *str) {
    while (*str != '\0')
        putchar(*str++);
    return 0;
}
