#include <catch2/catch.hpp>
#include <myos/kernel/ram/PageManager.hpp>

using myos::kernel::ram::PageManager;

TEST_CASE("ram::PageManager") {
    void *start = reinterpret_cast<void *>(0x200000);
    PageManager pageFrameManager(start, 4096, 256);
    void *f1 = pageFrameManager.newPage();
    void *f2 = pageFrameManager.newPage();
    REQUIRE(f1 != f2);
    REQUIRE(f1 >= start);
    REQUIRE(f2 >= start);
    REQUIRE(reinterpret_cast<intptr_t>(f2) - reinterpret_cast<intptr_t>(f1) >= 4096);
    pageFrameManager.releasePage(f1);
    pageFrameManager.releasePage(f2);
}