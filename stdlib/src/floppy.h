#ifndef FLOPPY_H_
#define FLOPPY_H_
#include <stdint.h>

void loadSector(uint8_t *buffer, uint32_t lba);

#endif