#include <stdio.h>

int main() {
    char ch = 'A';
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (1) {
        setChar(13, 40, ch);
        if (ch == 'Z') {
            ch = 'A';
        } else {
            ch++;
        }
    }
#pragma clang diagnostic pop
    return 0;
}

void sleep() {
    for (size_t i = 0; i < 1000000; ++i) {
        asm volatile("nop");
    }
}
