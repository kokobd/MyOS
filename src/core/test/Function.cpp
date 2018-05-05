#include <catch2/catch.hpp>
#include <myos/core/Function.hpp>

#include <iostream>

using myos::core::Function;

TEST_CASE("Function", "[unit]") {
    SECTION("void()") {
        int x = 0;
        Function<void()> f = [&x]() {
            x = 42;
        };
        f();
        REQUIRE(x == 42);
    }

    SECTION("int(double, double)") {
        Function<int(double, double)> f = [](double x, double y) {
            return (x + y) / 2;
        };

        REQUIRE(f(3, 4) == 3);
    }
}