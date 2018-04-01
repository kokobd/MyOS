#pragma once

#include <stdint.h>
#include <stdbool.h>

#pragma push_macro("NS")
#define NS(X) kernel_filesystem_fat12_ ## X

typedef int32_t (*NS(SectorLoader))(uint8_t *, uint32_t);

typedef struct {
    NS(SectorLoader) sectorLoader;
} NS(FAT12);

#define FAT12_FILENAME_SIZE 11

typedef struct {
    char name[FAT12_FILENAME_SIZE + 1];
    uint16_t firstCluster;
    uint32_t size;
    int32_t index;
} NS(File);

/**
 * Initialize an FAT12 object.
 * @param fat12 pointer to an uninitialized FAT12 object
 * @param sectorLoader Pointer to a function to load sectors.
 */
void NS(fat12Init)(NS(FAT12) *fat12, NS(SectorLoader) sectorLoader);

/**
 * Get meta information of a file. The returned struct can be used
 * as parameter in other functions in this module.
 * @param fat12 pointer to an FAT12 object
 * @param fileName strlen(fileName) MUST be 11, with all letters in UPPER CASE.
 * @return A struct containing meta information of that file.
 */
NS(File) NS(fat12GetFileByName)(NS(FAT12) *fat12, const char *fileName);

inline static const char *NS(fileGetName)(const NS(File) *file) {
    return file->name;
}

inline static uint32_t NS(fileGetSize)(const NS(File) *file) {
    return file->size;
}

inline static bool NS(fileExists)(const NS(File) *file) {
    return file->size != 0;
}

/**
 * Read all bytes from a file into memory.
 * @param fat12 pointer to an FAT12 object.
 * @param file the file to read from
 * @param dest where to put file contents
 * @return 0 on success, other values on failure.
 */
int32_t NS(fileReadAllBytes)(
        NS(FAT12) *fat12,
        const NS(File) *file,
        uint8_t *dest);

#pragma pop_macro("NS")
