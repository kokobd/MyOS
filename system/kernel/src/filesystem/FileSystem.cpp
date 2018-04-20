#include <myos/kernel/filesystem/FileSystem.hpp>
#include <cstring>
#include <cctype>

namespace myos::kernel::filesystem {

inline uint16_t clusterToIndex(uint16_t cluster) {
    return cluster + static_cast<uint16_t>(31);
}

inline uint16_t indexToCluster(uint16_t index) {
    return index - static_cast<uint16_t>(31);
}

FileSystem::FAT::FAT(SectorReader &sectorReader)
        : sectorReader(sectorReader),
          bufferIndex(1),
          bufferSize(sectorReader.sectorSize()) {
    buffer = new uint8_t[bufferSize];
    sectorReader.readSector(buffer, bufferIndex);
}

uint32_t FileSystem::FAT::operator[](uint32_t index) {
    const uint16_t cluster = indexToCluster(static_cast<uint16_t>(index));

    const uint32_t firstByteIndex = cluster * 3u / 2u;
    const uint32_t secondByteIndex = firstByteIndex + 1;
    const uint8_t firstByte = getByte(firstByteIndex);
    const uint8_t secondByte = getByte(secondByteIndex);
    const uint16_t word =
            firstByte | (static_cast<uint16_t>(secondByte) << 8u);
    const uint16_t nextCluster = (cluster % 2 != 0
                                  ? (word >> 4) : word) & (uint16_t) 0x0FFF;

    if (nextCluster < 0xFF7) {
        return clusterToIndex(nextCluster);
    }
    return 0xFFFFFFFF;
}

FileSystem::FAT::~FAT() {
    delete[] buffer;
}

uint8_t FileSystem::FAT::getByte(uint32_t byteIndex) {
    uint32_t expectedBufferIndex =
            byteIndex / sectorReader.sectorSize() + 1;
    if (expectedBufferIndex != bufferIndex) {
        sectorReader.readSector(buffer, expectedBufferIndex);
        bufferIndex = expectedBufferIndex;
    }
    return buffer[byteIndex % sectorReader.sectorSize()];
}

FileSystem::FileSystem(SectorReader &sectorReader)
        : sectorReader(sectorReader),
          fat(sectorReader) {
}

void FileSystem::closeFile(FileHandle file) {
    if (isHandleValid(file))
        files[file].inUse = false;
}

FileSystem::FileHandle FileSystem::openFile(const char *path) {
    File *file = nullptr;
    for (size_t i = 0; i < MAX_FILES; ++i) {
        if (!files[i].inUse) {
            file = files + i;
            break;
        }
    }
    if (file == nullptr) {
        return -1;
    }
    file->inUse = true;
    convertFileName(path, file->fileName);

    uint8_t buffer[sectorReader.sectorSize()];
    bool found = false;
    for (uint32_t i = 19; i < 33; ++i) {
        sectorReader.readSector(buffer, i);

        for (uint32_t j = 0; j < 512 / 32; ++j) {
            uint8_t *entry = buffer + j * 32;
            char name[12] = {'\0'};
            memcpy(name, entry, 11);
            if (strcmp(name, file->fileName) == 0) {
                file->firstSector =
                        clusterToIndex(*(uint16_t *) (entry + 0x1A));
                file->size = *(uint32_t *) (entry + 28);
                found = true;
                goto endLoop;
            }
        }
    }
    endLoop:
    if (found) {
        return static_cast<FileHandle>(file - files);
    } else {
        file->inUse = false;
        return -1;
    }
}

bool FileSystem::readAllBytes(FileSystem::FileHandle fileHandle, void *destination) {
    if (!isHandleValid(fileHandle)) {
        return false;
    }
    uint8_t *dest = reinterpret_cast<uint8_t *>(destination);
    uint32_t sector = files[fileHandle].firstSector;
    uint8_t buffer[sectorReader.sectorSize()];
    while (sector != 0xFFFFFFFF) {
        sectorReader.readSector(buffer, sector);
        sector = fat[sector];
        size_t len = sectorReader.sectorSize();
        if (sector == 0xFFFFFFFF) {
            len = files[fileHandle].size % sectorReader.sectorSize();
        }
        memcpy(dest, buffer, len);
        dest += sectorReader.sectorSize();
    }

    return true;
}

size_t FileSystem::getSize(FileSystem::FileHandle fileHandle) {
    if (isHandleValid(fileHandle)) {
        return files[fileHandle].size;
    }
    return 0;
}

bool FileSystem::convertFileName(const char *fileName, char *fat12FileName) {
    memset(fat12FileName, ' ', 11);
    fat12FileName[11] = '\0';

    size_t dotIndex = 0;
    while (fileName[dotIndex] != '\0'
           && dotIndex <= 8
           && fileName[dotIndex] != '.') {
        ++dotIndex;
    }
    if (dotIndex > 8 || fileName[dotIndex] == '\0')
        return false;
    for (size_t i = 0; i < dotIndex; ++i) {
        fat12FileName[i] = (char) toupper(fileName[i]);
    }

    size_t fileNameSize = strlen(fileName);
    size_t extSize = fileNameSize - 1 - dotIndex;
    if (extSize > 3)
        return false;
    for (size_t i = 0; i < extSize; ++i) {
        fat12FileName[10 - i] = fileName[fileNameSize - 1 - i];
    }
    return true;
}

bool FileSystem::isHandleValid(FileSystem::FileHandle fileHandle) {
    return fileHandle >= 0 && fileHandle < MAX_FILES
           && files[fileHandle].inUse;
}

}
