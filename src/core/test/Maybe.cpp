#include <catch2/catch.hpp>
#include <myos/core/Maybe.hpp>

using myos::core::Function;
using myos::core::Maybe;
using myos::core::fmap;

TEST_CASE("Maybe", "[unit]") {
    Maybe<int32_t> m1 = Maybe<int32_t>::just(12);
    Maybe<int32_t> m2 = Maybe<int32_t>::nothing();

    REQUIRE(m1.isJust());
    REQUIRE(m2.isNothing());

    m2 = m1;
    REQUIRE(m2.isJust());

    Function<int32_t(const int32_t &x)> f1 = [](const int32_t &x) -> int32_t { return x + 2; };
    m2 = fmap(m2, f1);

    Function<void(const int32_t &x)> onJust = [](const int32_t &x) {
        REQUIRE(x == 14);
    };
    Function<void()> onNothing = []() {
        REQUIRE(false);
    };
    m2.match(onJust, onNothing);
}