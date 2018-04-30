#include <catch2/catch.hpp>
#include <myos/core/cstring>
#include <cstdint>
#include <cstring>

TEST_CASE("cstring") {
    const char *empty = "";

    using namespace myos;

    SECTION("strlen works") {
        REQUIRE(0 == core::strlen(empty));
        REQUIRE(13 == core::strlen("hello, world."));
    }

    SECTION("strcmp works") {
        REQUIRE(0 == core::strcmp("", empty));

        REQUIRE(core::strcmp("abc", "bcd") < 0);
        REQUIRE(core::strcmp("abc", "abcd") < 0);
        REQUIRE(core::strcmp("", "abc") < 0);

        REQUIRE(core::strcmp("bcd", "abc") > 0);
        REQUIRE(core::strcmp("abcd", "abc") > 0);
        REQUIRE(core::strcmp("abc", "") > 0);
    }

    SECTION("memcpy works") {
        char dest[10] = {'\0'};
        char src[10] = "hello,wor";

        REQUIRE(strcmp(dest, src) != 0);
        core::memcpy(dest, src, 0);
        REQUIRE(strlen(dest) == 0);
        core::memcpy(dest, src, 5);
        REQUIRE(strcmp(dest, "hello") == 0);
        core::memcpy(dest, src, 10);
        REQUIRE(strcmp(dest, src) == 0);
    }

    SECTION("memset works") {
        char buf[10] = "hello,";
        core::memset(buf, '\0', 10);
        REQUIRE(strlen(buf) == 0);
        core::memset(buf, 'a', 9);
        buf[9] = '\0';
        REQUIRE(strcmp(buf, "aaaaaaaaa") == 0);
    }
}