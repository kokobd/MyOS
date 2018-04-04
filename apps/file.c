#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    const char *args = getArgs();
    const char *beg = args;
    while (*beg != '\0' && !isspace(*beg)) {
        ++beg;
    }
    while (*beg != '\0' && isspace(*beg))
        ++beg;
    const char *end = beg;
    while (*end != '\0' && !isspace(*end))
        ++end;


    char fileName[40];
    memset(fileName, 0, 40);
    memcpy(fileName, beg, end - beg);

    for (char *pt = fileName; *pt != '\0'; ++pt) {
        *pt = (char) toupper(*pt);
    }
    size_t fileSize = getFileSize(fileName);
    if (fileSize == 0) {
        puts("File doesn't exist.\n");
    } else {
        puts("Name: ");
        puts(fileName);
        putchar('\n');
        puts("Size: ");

        char fileSizeStr[30];
        char *fileSizeStrEnd = fileSizeStr + 1;
        while (fileSize > 0) {
            *fileSizeStrEnd = (char) (fileSize % 10 + '0');
            ++fileSizeStrEnd;
            fileSize /= 10;
        }
        for (const char *pt = fileSizeStrEnd - 1; pt != fileSizeStr; --pt) {
            putchar(*pt);
        }
        putchar('\n');
    }
    return 0;
}