#include <stdio.h>

int main() {
    for (size_t i = 0; i < 80 * 25; ++i) {
        putchar('\b');
    }
    return 0;
}
