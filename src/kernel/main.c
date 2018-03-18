#include <stdio.h>
#include <stdbool.h>

void _start() {
    putchar(12, 39, 'A');
    changeAttribute(12, 39, false, true, WHITE, BLUE);
}