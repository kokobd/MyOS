#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef int32_t (*SectorLoader)(uint8_t *, uint32_t);

struct FAT12 {
    SectorLoader sectorLoader;
};

#define FAT12_FILENAME_SIZE 11

struct FAT12File {
    char name[FAT12_FILENAME_SIZE + 1];
    uint16_t firstCluster;
    uint32_t size;
    int32_t index;
};

/**
 * Initialize an FAT12 object.
 * @param fat12 pointer to an uninitialized FAT12 object
 * @param sectorLoader Pointer to a function to load sectors.
 */
void fat12Init(struct FAT12 *fat12, SectorLoader sectorLoader);

/**
 * Get meta information of a file. The returned struct can be used
 * as parameter in other functions in this module.
 * @param fat12 pointer to an FAT12 object
 * @param fileName strlen(fileName) MUST be 11, with all letters in UPPER CASE.
 * @return A struct containing meta information of that file.
 */
struct FAT12File fat12GetFileByName(struct FAT12 *fat12, const char *fileName);

inline static const char *fat12FileGetName(const struct FAT12File *file) {
    return file->name;
}

inline static uint32_t fat12FileGetSize(const struct FAT12File *file) {
    return file->size;
}

inline static bool fat12FileExists(const struct FAT12File *file) {
    return file->size != 0;
}

/**
 * Read all bytes from a file into memory.
 * @param fat12 pointer to an FAT12 object.
 * @param file the file to read from
 * @param dest where to put file contents
 * @return 0 on success, other values on failure.
 */
int32_t fat12FileReadAllBytes(
        struct FAT12 *fat12,
        const struct FAT12File *file,
        uint8_t *dest);
