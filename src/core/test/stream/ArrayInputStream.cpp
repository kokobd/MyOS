#include <catch2/catch.hpp>
#include <myos/core/stream/ArrayInputStream.hpp>
#include <cstdint>

using myos::core::stream::InputStream;
using myos::core::stream::ArrayInputStream;

TEST_CASE("stream::ArrayInputStream") {
    uint8_t data[4] = {0, 1, 2, 3};
    ArrayInputStream<uint8_t> stream(data, 4);
    InputStream<uint8_t> &streamRef = stream;
    uint8_t i = 0;
    while (streamRef.hasNext()) {
        uint8_t value = streamRef.next();
        REQUIRE(value == i++);
    }
    REQUIRE(!streamRef.hasNext());
}
