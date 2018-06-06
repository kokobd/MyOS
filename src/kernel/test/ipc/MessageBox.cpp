#include <catch2/catch.hpp>
#include <myos/kernel/ipc/MessageBox.hpp>
#include <vector>
#include <cstdint>

using myos::kernel::ipc::MsgBoxMetaInfo;
using myos::kernel::ipc::MessageBox;

TEST_CASE("ipc::MessageBox") {
    const uint8_t MAX_COUNT = 32;
    const uint8_t MSG_SIZE = 8;

    MsgBoxMetaInfo metaInfo;
    metaInfo.msgSize = MSG_SIZE;
    metaInfo.msgMaxCount = MAX_COUNT;
    std::vector<uint8_t> memory(MSG_SIZE * (size_t) MAX_COUNT);
    metaInfo.memory = memory.data();

    MessageBox messageBox(metaInfo);

    SECTION("Initial state") {
        REQUIRE(messageBox.isEmpty());
        REQUIRE(!messageBox.isFull());
        REQUIRE(messageBox.location() == reinterpret_cast<uintptr_t>(memory.data()));
        REQUIRE(messageBox.sizeInBytes() == memory.size());
    }

    SECTION("Push until full") {
        for (uint8_t i = 0; i < MAX_COUNT; ++i) {
            uint32_t message = i;
            messageBox.push(&message);
            if (i != MAX_COUNT - 1) {
                REQUIRE_FALSE(messageBox.isFull());
            } else {
                REQUIRE(messageBox.isFull());
            }
        }

        SECTION("then pop") {
            uint32_t buffer;
            messageBox.pop(&buffer);
            REQUIRE(buffer == 0);
            REQUIRE_FALSE(messageBox.isFull());

            SECTION("then push again") {
                buffer = 0;
                messageBox.push(&buffer);
                REQUIRE(messageBox.isFull());

                SECTION("then pop until empty") {
                    for (uint8_t i = 0; i < MAX_COUNT; ++i) {
                        REQUIRE_FALSE(messageBox.isEmpty());
                        messageBox.pop(&buffer);
                    }
                    REQUIRE(messageBox.isEmpty());
                    REQUIRE(buffer == 0);
                }
            }
        }
    }

    SECTION("move message box") {
        uint32_t message = 42;
        messageBox.push(&message);
        messageBox.push(&message);

        std::vector<uint8_t> newMemory = memory;
        for (uint8_t &x : newMemory) {
            x = 0;
        }
        messageBox.moveData(newMemory.data());
        uint32_t buffer;
        messageBox.pop(&buffer);
        REQUIRE(buffer == 42);
        messageBox.pop(&buffer);
        REQUIRE(buffer == 42);
        REQUIRE(messageBox.isEmpty());
    }

}