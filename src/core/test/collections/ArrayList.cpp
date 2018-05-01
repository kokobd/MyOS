#include <catch2/catch.hpp>
#include <myos/core/collections/ArrayList.hpp>
#include <iostream>

using myos::core::collections::ArrayList;

namespace {

struct Int {
    Int(int32_t value = 0)
            : value(value) {
        ++ctor_times;
    }
    Int(const Int &obj) {
        ++ctor_times;
        value = obj.value;
    }

    Int &operator=(const Int &that) {
        value = that.value;
        return *this;
    }

    ~Int() {
        ++dtor_times;
    }

    friend bool operator==(const Int &lhs, const Int &rhs);

    friend std::ostream &operator<<(std::ostream &os, const Int &x) {
        return os << x.value;
    }

    static size_t ctor_times;
    static size_t dtor_times;

    static void reinit() {
        ctor_times = 0;
        dtor_times = 0;
    }

    int32_t value;
};

size_t Int::ctor_times = 0;
size_t Int::dtor_times = 0;

bool operator==(const Int &lhs, const Int &rhs) {
    return lhs.value == rhs.value;
}

}

TEST_CASE("collections::ArrayList<E>", "[unit]") {
    {
        ArrayList<Int> list;

        SECTION("empty list") {
            REQUIRE(list.size() == 0);
            REQUIRE(list.isEmpty());

            REQUIRE(Int::ctor_times == 0);
            REQUIRE(Int::dtor_times == 0);
        }

        SECTION("add and remove") {
            for (int32_t i = 0; i < 64; ++i) {
                list.add(Int(i));
                REQUIRE(list.size() == i + 1);
                REQUIRE(list.last() == i);
            }

            list.remove(1);
            REQUIRE(list.size() == 63);
            REQUIRE(list.first() == 0);
            REQUIRE(list[1] == 2);

            list.remove(100);
            REQUIRE(list.size() == 63);
            list.remove(list.size() - 1);
            REQUIRE(list.last() == 62);
            REQUIRE(list.size() == 62);
        }

    }

    REQUIRE(Int::ctor_times == Int::dtor_times);
}
