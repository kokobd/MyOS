#include <stdio.h>
#include "floppy.h"

static char * const video = (char *) 0xb8000;

static inline bool checkBoundary(int row, int col) {
    return row >= 0 && row < 25 && col >= 0 && col < 80;
}

bool putchar(int row, int col, char ch) {
    if (!checkBoundary(row, col))
        return false;
    *(video + (80 * row + col) * 2) = ch;
    return true;
}

bool changeAttribute(
    int row, int col,
    bool blink,
    bool foregroundIntensity,
    enum Color foregroundColor,
    enum Color backgroundColor)
{
    if (!checkBoundary(row, col))
        return false;
    unsigned char attribute = 0;
    if (blink)
        attribute |= 0b10000000;
    if (foregroundIntensity)
        attribute |= 0b00001000;
    attribute |= (foregroundColor & 0b00000111);
    attribute |= ((backgroundColor << 4) & 0b01110000);
    *(video + (80 * row + col) * 2 + 1) = attribute;

    return true;
}

static int findFile(char *root, const char *name);
static uint16_t nextSector(uint16_t currentSector);
static uint16_t nextCluster(uint16_t cluster, const uint8_t *fat);

size_t loadFile(const char *fileName, uint8_t *buffer) {
    const char *pt = fileName;
    int col = 0;
    while (*pt != '\0' && *pt != '.') {
        ++col;
        ++pt;
    }
    const char * const dot = pt;

    char name[11] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int i = 0;
    for (pt = fileName; pt != dot; ++pt) {
        if (i == 8) {
            break;
        }
        name[i] = *pt;
        ++i;
    }
    i = 0; // TODO Need fix
    for (pt = dot + 1; *pt != '\0'; ++pt) {
        if (i == 3)
            break;
        name[8 + i] = *pt;
        ++i;
    }

    const int ROOT_DIR_SECTORS = ((224 * 32) + (512 - 1)) / 512;
    char * const temp = (char *) 0x150000;
    loadSector(temp, 19); // 加载根目录区的第一个扇区到temp
    // 下面temp代表FAT表
    // 我们现在文件数量很少，加载一个扇区就够用了。实际上这个代码是不严谨的。

    int fileCluster = findFile(temp, name); // 数据区第一个cluster的序号为2
    loadSector(temp, 1); // 加载1号FAT表的第一个扇区
    putchar(0, 0, 'B');
    
    size_t fileSize = 0;
    do {
        loadSector(buffer, 19 + ROOT_DIR_SECTORS + fileCluster - 2);
        fileCluster = nextCluster(fileCluster, temp);
        buffer += 512;
        fileSize += 512;
    } while (fileCluster < 0xFF7);
    return fileSize;
}

/**
 * 从给定的FAT表中查找下一个cluster。
 * 按照FAT12的规范，如果返回值>=0xFF8，表示没有下一个cluster
 * 如果返回值==0xFF7，表示下一个是个坏cluster
 */
static uint16_t nextCluster(uint16_t cluster, const uint8_t *fat) {
    if (cluster % 2 == 0) {
        int index = cluster / 2 * 3;
        uint16_t next = fat[index];
        next |= (fat[index + 1] & 0x0F) << 8;
        return next;
    } else {
        int index = (cluster - 1) / 2 * 3 + 1;
        uint16_t next = (fat[index] & 0xF0) >> 4;
        next |= fat[index + 1] << 4;
        return next;
    }
}

/**
 * name 必须是长度为11的文件名。这里不检查'\0'
 * 如果找到文件，返回逻辑扇区号，否则返回-1
 */
static int findFile(char *root, const char *name) {
    int i = 0;
    bool ended = false;
    int result = -1;
    do {
        char *cur = root + i * 32;
        bool match = true;
        // compare cur[0..10] with name[0..10]
        for (int j = 0; j < 11; j++) {
            if (cur[j] != name[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            ended = true;
            result = *(uint16_t *) (cur + 0x1A);
        }
        ++i;
        if (i == 244)
            ended = true;
    } while (!ended);
    return result;
}

static void inb(void *port, uint8_t *val) {
    __asm__(
        "in %0, dx"
        : "=r" (*val)
        : "d" (port)
        :
    );
}

char getchar() {
    bool hasInput = false;
    do {
        uint8_t status;
        inb((void *) 0x64, &status); // read keyboard status
        hasInput = (status & 0x01) == 0x01;
    } while (!hasInput);
    char input = '/'; // dumb input
    inb((void *) 0x60, &input);
    return input;
}