#include <catch2/catch.hpp>
#include <myos/core/String.hpp>

#include <string>

using myos::core::String;

std::ostream &operator<<(std::ostream &os, const String &string) {
    for (size_t i = 0; i < string.size(); ++i) {
        os << string[i];
    }
    return os;
}

namespace Catch {
template<>
struct StringMaker<String> {
    static std::string convert(const String &value) {
        std::string ret;
        for (size_t i = 0; i < value.size(); ++i) {
            ret += value[i];
        }
        return ret;
    }
};

}

TEST_CASE("String", "[unit]") {
    String abc("abc");

    REQUIRE(abc == String("abc"));
    REQUIRE(String("") == String(""));

    REQUIRE(String("abcd").size() == 4);
    REQUIRE(String("").size() == 0);
    REQUIRE(String().size() == 0);
    REQUIRE(abc.length() == 3);

    REQUIRE(abc.first() == 'a');
    REQUIRE(abc.last() == 'c');

    String dbc = abc;
    REQUIRE(dbc == abc);
    dbc.first() = 'd';
    REQUIRE(dbc == String("dbc"));
}
