#pragma once

#include <myos/kernel/drivers/Floppy.hpp>
#include "SectorReader.hpp"

namespace myos::kernel::filesystem {

class FileSystem {
private:
    /**
     * Represents file allocation table in FAT12
     */
    class FAT {
    public:
        explicit FAT(SectorReader &sectorReader);

        /**
         * Given a sector index, returns the next sector
         * index in the same file. If this is the last sector,
         * returns 0xFFFFFFFF
         */
        uint32_t operator[](uint32_t index);

        ~FAT();

    private:
        uint8_t getByte(uint32_t byteIndex);

    private:
        SectorReader &sectorReader;

        uint8_t *buffer;

        uint32_t bufferIndex;

        size_t bufferSize;
    };

public:
    explicit FileSystem(SectorReader &sectorReader);

    using FileHandle = int32_t;

    FileHandle openFile(const char *path);

    size_t getSize(FileHandle fileHandle);

    void closeFile(FileHandle file);

    bool readAllBytes(FileHandle handle, void *destination);

private:
    SectorReader &sectorReader;

    FAT fat;

    struct File {
        uint32_t firstSector;
        size_t size;
        char fileName[12];
        bool inUse;

        File() : firstSector(0xFFFFFFFF),
                 size(0),
                 fileName{'\0'},
                 inUse(false) {}
    };

    static constexpr int32_t MAX_FILES = 8;
    File files[MAX_FILES];

    bool convertFileName(const char *fileName, char *fat12FileName);

    bool isHandleValid(FileHandle fileHandle);
};

}
