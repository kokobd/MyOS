#include <stdbool.h>
#include <string.h>
#include "fat12.h"

static uint16_t nextCluster(uint16_t cluster, const uint8_t *fat);

void fat12Init(struct FAT12 *this, SectorLoader sectorLoader) {
    this->sectorLoader = sectorLoader;
}

struct FAT12File fat12GetFileByName(struct FAT12 *this, const char *fileName) {
    // Each sector is 512 bytes
    // Root directory: [19..33), has 14 sectors
    //   Each entry in root directory area has 32 bytes
    struct FAT12File result;
    result.size = 0;
    result.name[FAT12_FILENAME_SIZE] = '\0';
    uint8_t sector[512];
    for (uint32_t i = 19; i < 33; ++i) {
        this->sectorLoader(sector, 19);

        for (uint32_t j = 0; j < 512 / 32; ++j) {
            uint8_t *entry = sector + j * 32;
            char name[FAT12_FILENAME_SIZE + 1] = {0};
            memcpy(name, entry, FAT12_FILENAME_SIZE);
            if (strcmp(fileName, name) == 0) {
                result.firstCluster = *(uint16_t *) (entry + 0x1A);
                result.size = *(uint32_t *) (entry + 0x1C);
                goto end;
            }
        }
    }
    end:
    return result;
}

int32_t fat12FileReadAllBytes(
        struct FAT12 *this,
        const struct FAT12File *file,
        uint8_t *dest) {
    if (!fat12FileExists(file))
        return -1;
    uint8_t fatSector0[512];
    this->sectorLoader(fatSector0, 1);

    uint16_t cluster = file->firstCluster;
    uint8_t buffer[512];
    while (cluster < 0xFF7) {
        this->sectorLoader(buffer, cluster + (uint16_t) 31);
        cluster = nextCluster(cluster, fatSector0);
        if (cluster >= 0xFF8) {
            uint32_t lastPartSize = fat12FileGetSize(file) % 512;
            memcpy(dest, buffer, lastPartSize);
        } else {
            memcpy(dest, buffer, 512);
            dest += 512;
        }
    }
    if (cluster == 0xFF7)
        return -1;
    return 0;
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
        uint16_t next = (uint16_t) ((fat[index] & 0xF0) >> 4);
        next |= fat[index + 1] << 4;
        return next;
    }
}
