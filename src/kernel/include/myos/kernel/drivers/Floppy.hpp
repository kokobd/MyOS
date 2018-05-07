#pragma once

#include <cstddef>
#include <myos/kernel/cpu/InterruptHandler.hpp>
#include <myos/kernel/filesystem/SectorReader.hpp>

namespace myos::kernel::drivers {

class Floppy : public filesystem::SectorReader {
public:
    Floppy();

    bool readSector(uint8_t *dest, uint32_t lba) override;

private:
    volatile bool sectorReadFinished = false;

    void *buffer;

    class InterruptHandlerImpl : public cpu::InterruptHandler {
    public:
        explicit InterruptHandlerImpl(volatile bool &sectorReadFinished)
                : sectorReadFinished(sectorReadFinished) {}

        void handleInterrupt(cpu::InterruptType interrupt,
                             cpu::RegisterState &registerState) override;

    private:
        volatile bool &sectorReadFinished;
    };

    InterruptHandlerImpl interruptHandler;

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

    uint8_t getMsr();

    void waitUntilReady();

    /**
     * Convert LBA(Logical Block Addressing) to CHS(Cylinder, Head, Sector)
     */
    void lbaToChs(uint32_t lba, uint16_t *cyl, uint16_t *head, uint16_t *sector) {
#define SECTORS_PER_TRACK 18
        *cyl = (uint16_t) (lba / (2 * SECTORS_PER_TRACK));
        *head = (uint16_t) ((lba % (2 * SECTORS_PER_TRACK)) / SECTORS_PER_TRACK);
        *sector = (uint16_t) ((lba % (2 * SECTORS_PER_TRACK)) % SECTORS_PER_TRACK + 1);
#undef SECTORS_PER_TRACK
    }

    void sendCommand(uint8_t command);

    void writeDOR(uint8_t data);

    void setupDMA();

    uint8_t readData();

};

}
