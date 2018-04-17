#include <stdio.h>

void sleep();

int main() {

    return 0;
}

void sleep() {
    for (size_t i = 0; i < 100000; ++i) {
        asm volatile("nop");
    }
}
