#include <string.h>
#include <ctype.h>
#include "file.h"
#include "fat12.h"
#include "../floppy/floppy.h"

#define NS(X) kernel_filesystem_file_ ## X
#define fat12(X) kernel_filesystem_fat12_ ## X

typedef struct {
    fat12(File) fat12File;
    bool opened;
    int32_t position;
} File;

#define MAX_HANDLES 256

static fat12(File) files[MAX_HANDLES] = {0};
static bool handleOccupied[MAX_HANDLES];

void NS(init)() {
    memset(files, 0, MAX_HANDLES * sizeof(fat12(File)));
    memset(handleOccupied, 0, MAX_HANDLES * sizeof(bool));
}

int32_t NS(fopen)(const char *fileName, uint32_t flags) {
    char fat12FileName[11] = {' '};

    size_t dotIndex = 0;
    while (fileName[dotIndex] != '\0'
           && dotIndex <= 8
           && fileName[dotIndex] != '.') {
        ++dotIndex;
    }
    if (dotIndex > 8 || fileName[dotIndex] == '\0')
        return -1;
    for (size_t i = 0; i < dotIndex; ++i) {
        fat12FileName[i] = (char) toupper(fileName[i]);
    }

    size_t fileNameSize = strlen(fileName);
    size_t extSize = fileNameSize - 1 - dotIndex;
    if (extSize > 3)
        return -1;
    for (size_t i = 0; i < extSize; ++i) {
        fat12FileName[10 - i] = fileName[fileNameSize - 1 - i];
    }

    // Now, we are sure that filename is legal.
    fat12(FAT12) fat12;
    fat12(fat12Init)(&fat12, kernel_floppy_loadSector);
    fat12(File) file = fat12(fat12GetFileByName)(&fat12, fat12FileName);
    if (!fat12(fileExists)(&file)) {
        return -1;
    }
    int32_t i = 0;
    for (; i < 256; ++i) {
        if (!fat12(fileExists)(files + i)) {
            files[i] = file;
            break;
        }
    }
    if (i == 256) { // resource exhausted
        return -1;
    }

    handleOccupied[i] = true;
    return i;
}

int32_t NS(fread)(int32_t fileHandle, uint8_t *dest, size_t limit) {
    if (0 <= fileHandle && fileHandle < MAX_HANDLES) {

    }
}

int32_t NS(fclose)(int32_t fileHandle) {
    if (0 <= fileHandle && fileHandle < MAX_HANDLES)
        handleOccupied[fileHandle] = false;
}
