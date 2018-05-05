#include <catch2/catch.hpp>
#include <cctype>
#include <myos/core/cctype>

using namespace myos;

TEST_CASE("ctype", "[unit]") {

    SECTION("all is** functions") {
        for (char ch = 0; ch <= 127 && ch >= 0; ++ch) {
            REQUIRE((bool) islower(ch) == (bool) core::islower(ch));
            REQUIRE((bool) isupper(ch) == (bool) core::isupper(ch));
            REQUIRE((bool) isalpha(ch) == (bool) core::isalpha(ch));
            REQUIRE((bool) isdigit(ch) == (bool) core::isdigit(ch));
            REQUIRE((bool) isalnum(ch) == (bool) core::isalnum(ch));
            REQUIRE((bool) isspace(ch) == (bool) core::isspace(ch));
        }
    }

    SECTION("tolower") {
        REQUIRE('a' == core::tolower('a'));
        REQUIRE('a' == core::tolower('A'));
        REQUIRE('e' == core::tolower('e'));
        REQUIRE('e' == core::tolower('E'));
        REQUIRE('z' == core::tolower('z'));
        REQUIRE('z' == core::tolower('Z'));

        REQUIRE('*' == core::tolower('*'));
    }

    SECTION("toupper") {
        REQUIRE('A' == core::toupper('a'));
        REQUIRE('A' == core::toupper('A'));
        REQUIRE('H' == core::toupper('h'));
        REQUIRE('H' == core::toupper('H'));
        REQUIRE('Z' == core::toupper('z'));
        REQUIRE('Z' == core::toupper('Z'));

        REQUIRE('*' == core::toupper('*'));
    }
}
