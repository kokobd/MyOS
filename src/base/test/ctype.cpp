#include <catch2/catch.hpp>
#include <cctype>
#include <myos/base/cctype>

using namespace myos;

TEST_CASE("ctype") {

    SECTION("all is** functions") {
        for (char ch = 0; ch <= 127 && ch >= 0; ++ch) {
            REQUIRE((bool) islower(ch) == (bool) base::islower(ch));
            REQUIRE((bool) isupper(ch) == (bool) base::isupper(ch));
            REQUIRE((bool) isalpha(ch) == (bool) base::isalpha(ch));
            REQUIRE((bool) isdigit(ch) == (bool) base::isdigit(ch));
            REQUIRE((bool) isalnum(ch) == (bool) base::isalnum(ch));
            REQUIRE((bool) isspace(ch) == (bool) base::isspace(ch));
        }
    }

    SECTION("tolower") {
        REQUIRE('a' == base::tolower('a'));
        REQUIRE('a' == base::tolower('A'));
        REQUIRE('e' == base::tolower('e'));
        REQUIRE('e' == base::tolower('E'));
        REQUIRE('z' == base::tolower('z'));
        REQUIRE('z' == base::tolower('Z'));

        REQUIRE('*' == base::tolower('*'));
    }

    SECTION("toupper") {
        REQUIRE('A' == base::toupper('a'));
        REQUIRE('A' == base::toupper('A'));
        REQUIRE('H' == base::toupper('h'));
        REQUIRE('H' == base::toupper('H'));
        REQUIRE('Z' == base::toupper('z'));
        REQUIRE('Z' == base::toupper('Z'));

        REQUIRE('*' == base::toupper('*'));
    }
}
