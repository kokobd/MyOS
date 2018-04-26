#include <catch2/catch.hpp>
#include <myos/base/collections/BitSet.hpp>

using myos::base::collections::BitSet;

TEST_CASE("BitSet") {
    constexpr size_t length = 2048;
    BitSet bitSet(length);

    SECTION("size") {
        REQUIRE(length == bitSet.size());
    }

    SECTION("set and get") {
        for (size_t i = 0; i < length; ++i) {
            bool bit = bitSet.get(i);
            REQUIRE_FALSE(bit);
        }

        REQUIRE_FALSE(bitSet.get(0));
        bitSet.set(0);
        REQUIRE(bitSet.get(0));

        REQUIRE_FALSE(bitSet.get(31));
        bitSet.set(31);
        REQUIRE(bitSet.get(31));

        REQUIRE_FALSE(bitSet.get(32));
        bitSet.set(32);
        REQUIRE(bitSet.get(32));

        REQUIRE_FALSE(bitSet.get(length - 1));
        bitSet.set(length - 1);
        REQUIRE(bitSet.get(length - 1));

        REQUIRE_FALSE(bitSet.get(246));
        bitSet.set(246);
        REQUIRE(bitSet.get(246));
        bitSet.set(246, false);
        REQUIRE_FALSE(bitSet.get(246));
    }

    SECTION("findFirst") {
        bitSet.set(247);

        REQUIRE(bitSet.findFirst(true) == 247);

        for (size_t i = 0; i < 347; ++i) {
            bitSet.set(i, true);
        }
        REQUIRE(bitSet.findFirst(false) == 347);

        bitSet.set(348);
        bitSet.set(350);
        REQUIRE(bitSet.findFirst(false) == 347);
    }
}
