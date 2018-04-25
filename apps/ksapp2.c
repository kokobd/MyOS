#include <stdio.h>

void sleep();

int main() {
    char ch = 'A';
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    for (int i = 0; i < 50000; ++i) {
        setChar(13, 38, ch);
        if (ch == 'Z') {
            ch = 'A';
        } else {
            ch++;
        }
        sleep();
    }
#pragma clang diagnostic pop
    return 0;
}

void sleep() {
    for (size_t i = 0; i < 1000000; ++i) {
        asm volatile("nop");
    }
}
