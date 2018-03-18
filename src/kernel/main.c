#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

void _start() {
    uint8_t *app1 = (uint8_t *) 0x200000;
    // char fileName[10] = { 'K', 'R', 'N', 'L', 'D', 'R', '.', 'S', 'Y', 'S' };
    char fileName[10] = { 'K', 'E', 'R', 'N', 'E', 'L', '.', 'S', 'Y', 'S' };
    size_t fileSize = loadFile(fileName, app1);
    putchar(0, 0, fileSize / 512 + '0');
}