#ifndef MYOS_STDIO_H_
#define MYOS_STDIO_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * 直接向显示器写一个字符
 * 共有25行，80列。下标超出范围时什么也不会发生
 */
bool putchar(int row, int col, char ch);

enum Color {
    BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3,
    RED = 4, MAGENTA = 5, BROWN = 6, WHITE = 7
};

bool changeAttribute(
    int row, int col,
    bool blink,
    bool foregroundIntensity,
    enum Color foregroundColor,
    enum Color backgroundColor);

char getchar();

/**
 * 从软盘读取名为fileName的文件到buffer。返回文件大小。如果这个文件不存在，返回值为0
 * 注意，fileName必须形如yyyy.xxx，即使用dot分隔文件名和扩展名。文件名不能超过8个字符，
 * 扩展名必须是3个字符。违反的话后果自负。
 */
size_t loadFile(const char *fileName, uint8_t *buffer);

void disableCurser();

#endif