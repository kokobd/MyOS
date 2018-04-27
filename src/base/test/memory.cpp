#include <catch2/catch.hpp>
#include <myos/base/memory.hpp>

using namespace myos::base;

TEST_CASE("memory", "[unit]") {

    SECTION("alignUp") {
        REQUIRE(memory::alignUp(0, 123) == 123);
        REQUIRE(memory::alignUp(0, 0) == 0);

        REQUIRE(memory::alignUp(1, 124) == 124);
        REQUIRE(memory::alignUp(1, 125) == 126);

        REQUIRE(memory::alignUp(2, 120) == 120);
        REQUIRE(memory::alignUp(2, 121) == 124);
        REQUIRE(memory::alignUp(2, 122) == 124);
        REQUIRE(memory::alignUp(2, 123) == 124);
        REQUIRE(memory::alignUp(2, 124) == 124);
    }

    SECTION("log2") {
        REQUIRE(memory::log2(0) == 0);
        REQUIRE(memory::log2(1) == 0);
        REQUIRE(memory::log2(2) == 1);
        REQUIRE(memory::log2(3) == 1);
        REQUIRE(memory::log2(4) == 2);
        REQUIRE(memory::log2(5) == 2);
    }
}
