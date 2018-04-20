#include <myos/kernel/drivers/Floppy.hpp>
#include <myos/kernel/Kernel.hpp>
#include <myos/kernel/drivers/util.hpp>
#include <cstring>

namespace myos::kernel::drivers {

using util::inb;
using util::outb;

Floppy::Floppy() : interruptHandler(sectorReadFinished) {
    setSectorSize(512);
    Kernel::getCurrentKernel().getCPU()
            .registerInterruptHandler(cpu::InterruptType::FLOPPY,
                                      &interruptHandler);
}

bool Floppy::readSector(uint8_t *dest, uint32_t lba) {
    setupDMA();

    uint16_t cyl, head, sector;
    lbaToChs(lba, &cyl, &head, &sector);

    // Start motor, enable controller, select drive 0.
    writeDOR(0);
    for (int i = 0; i < 50000; ++i) {
        asm volatile("nop");
    }
    writeDOR(0b00011100);
    sectorReadFinished = false;
    asm volatile("sti");
    while (!sectorReadFinished);
    asm volatile("cli");

    sendCommand(8); // SENSE_INTERRUPT
    readData();
    readData();

    // send command to read sector
    uint8_t cmds[9] = {
            0b01000110,
            static_cast<uint8_t>(head << 2),
            (uint8_t) cyl,
            (uint8_t) head,
            (uint8_t) sector,
            2,
            1,
            42,
            0xFF
    };

    for (int i = 0; i < 9; ++i) {
        sendCommand(cmds[i]);
    }
    // Wait for IRQ6
    sectorReadFinished = false;
    asm volatile("sti");
    while (!sectorReadFinished);
    asm volatile("cli");
    for (int i = 0; i != 7; ++i) {
        readData();
    }

    memcpy(dest, buffer, 512);

    return true;
}

void Floppy::waitUntilReady() {
    bool ready;
    do {
        uint8_t msr = getMsr();
        ready = (msr & 0x80) == 0x80;
    } while (!ready);
}

uint8_t Floppy::getMsr() {
    return inb(MAIN_STATUS_REGISTER);
}

void Floppy::sendCommand(uint8_t command) {
    waitUntilReady();
    outb(DATA_FIFO, command);
}

void Floppy::writeDOR(uint8_t data) {
    outb(DIGITAL_OUTPUT_REGISTER, data);
}

void Floppy::setupDMA() {
    outb(0x0A, 0x06);
    outb(0x0C, 0xFF);
    // We will use 0x500 as the beginning of DMA buffer
    union {
        uint16_t address;
        struct {
            uint8_t low;
            uint8_t high;
        };
    } bufAddr{.address = 0x500};
    buffer = reinterpret_cast<void *>(bufAddr.address);
    outb(0x04, bufAddr.low);
    outb(0x04, bufAddr.high);

    outb(0x0C, 0xFF);
    outb(0x05, 0xFF);
    outb(0x05, 0x01);
    outb(0x81, 0);
    outb(0x0B, 0x46);
    outb(0x0A, 0x02);

}

uint8_t Floppy::readData() {
    waitUntilReady();
    return inb(DATA_FIFO);
}

void Floppy::InterruptHandlerImpl::handleInterrupt(
        cpu::InterruptType interrupt,
        cpu::RegisterState &registerState) {
    sectorReadFinished = true;
}

}
