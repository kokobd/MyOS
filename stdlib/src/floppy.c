#include "floppy.h"
#include <stdio.h>

/**
 * Convert LBA(Logical Block Addressing) to CHS(Cylinder, Head, Sector)
 */
static void lbaToChs(uint32_t lba, uint16_t* cyl, uint16_t* head, uint16_t* sector)
{
#define SECTORS_PER_TRACK 18
    *cyl    = lba / (2 * SECTORS_PER_TRACK);
    *head   = ((lba % (2 * SECTORS_PER_TRACK)) / SECTORS_PER_TRACK);
    *sector = ((lba % (2 * SECTORS_PER_TRACK)) % SECTORS_PER_TRACK + 1);
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

static void inb(void *port, uint8_t *val) {
    __asm__(
        "in %0, dx"
        : "=r" (*val)
        : "d" (port)
        :
    );
}

static void outb(void *port, uint8_t val) {
    __asm__(
        "out dx, al"
        :
        : "d" (port), "a" (val)
        :
    );
}

static uint8_t getMsr() {
    uint8_t msr = 0;
    inb((void *) MAIN_STATUS_REGISTER, &msr);
    return msr;
}

static void waitUntilReady() {
    bool ready = false;
    do {
        uint8_t msr = getMsr();
        ready = (msr & 0x80) == 0x80;
    } while (!ready);
}

void loadSector(uint8_t *buffer, uint32_t lba) {
    uint16_t cyl, head, sector;
    lbaToChs(lba, &cyl, &head, &sector);

    // Start motor, enable controller, select drive 0.
    outb((void *) DIGITAL_OUTPUT_REGISTER, 0b00010100);

    // send command to read sector
    uint8_t cmds[9] = {
        0b01000110,
        0,
        cyl,
        head,
        sector,
        2,
        1,
        42,
        0
    };
    for (int i = 0; i < 9; ++i) {
        waitUntilReady();
        outb((void *) DATA_FIFO, cmds[i]);
    }
    uint8_t *pt = buffer;
    while (true) {
        waitUntilReady();
        inb((void *) DATA_FIFO, pt);
        ++pt;
        if (pt - buffer == 512)
            break;
    }
    outb((void *) DIGITAL_OUTPUT_REGISTER, 0);
    int x = 0;
    while (x < 1000000) { // wait for some time
        ++x;
    }
}