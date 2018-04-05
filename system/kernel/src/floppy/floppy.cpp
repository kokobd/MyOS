#include "floppy.h"
#include "../hal/io.hpp"
#include <stdbool.h>

#define NS(X) kernel_floppy_ ## X

/**
 * Convert LBA(Logical Block Addressing) to CHS(Cylinder, Head, Sector)
 */
static void lbaToChs(uint32_t lba, uint16_t *cyl, uint16_t *head, uint16_t *sector) {
#define SECTORS_PER_TRACK 18
    *cyl = (uint16_t) (lba / (2 * SECTORS_PER_TRACK));
    *head = (uint16_t) ((lba % (2 * SECTORS_PER_TRACK)) / SECTORS_PER_TRACK);
    *sector = (uint16_t) ((lba % (2 * SECTORS_PER_TRACK)) % SECTORS_PER_TRACK + 1);
#undef SECTORS_PER_TRACK
}

enum FloppyRegisters {
    // r - read-only    w - write-only
            STATUS_REGISTER_A = 0x3F0, // r
    STATUS_REGISTER_B = 0x3F1, // r
    DIGITAL_OUTPUT_REGISTER = 0x3F2,
    TAPE_DRIVE_REGISTER = 0x3F3,
    MAIN_STATUS_REGISTER = 0x3F4, // r
    DATARATE_SELECT_REGISTER = 0x3F4, // w
    DATA_FIFO = 0x3F5,
    DIGITAL_INPUT_REGISTER = 0x3F7, // r
    CONFIGURATION_CONTROL_REGISTER = 0x3F7 // w
};

static uint8_t getMsr() {
    return inb(MAIN_STATUS_REGISTER);
}

static void waitUntilReady() {
    bool ready;
    do {
        uint8_t msr = getMsr();
        ready = (msr & 0x80) == 0x80;
    } while (!ready);
}

int32_t NS(loadSector)(uint8_t *buffer, uint32_t lba) {
    uint16_t cyl, head, sector;
    lbaToChs(lba, &cyl, &head, &sector);

    // Start motor, enable controller, select drive 0.
    outb(DIGITAL_OUTPUT_REGISTER, 0b00010100);

    // send command to read sector
    uint8_t cmds[9] = {
            0b01000110,
            0,
            (uint8_t) cyl,
            (uint8_t) head,
            (uint8_t) sector,
            2,
            1,
            42,
            0
    };
    for (int i = 0; i < 9; ++i) {
        waitUntilReady();
        outb(DATA_FIFO, cmds[i]);
    }
    uint8_t *pt = buffer;
    while (true) {
        waitUntilReady();
        *pt = inb(DATA_FIFO);
        ++pt;
        if (pt - buffer == 512)
            break;
    }
    outb(DIGITAL_OUTPUT_REGISTER, 0);
    volatile int x = 0; // avoid x from being optimized out
    while (x < 10000) { // wait for some time
        ++x;
    }
    return 0;
}