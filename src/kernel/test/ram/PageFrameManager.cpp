#include <catch2/catch.hpp>
#include <myos/kernel/ram/PageFrameManager.hpp>

using myos::kernel::ram::PageFrameManager;

TEST_CASE("ram::PageFrameManager") {
    void *start = reinterpret_cast<void *>(0x200000);
    PageFrameManager pageFrameManager(start, 4096, 256);
    void *f1 = pageFrameManager.allocatePageFrame();
    void *f2 = pageFrameManager.allocatePageFrame();
    REQUIRE(f1 != f2);
    REQUIRE(f1 >= start);
    REQUIRE(f2 >= start);
    REQUIRE(reinterpret_cast<intptr_t>(f2) - reinterpret_cast<intptr_t>(f1) >= 4096);
    pageFrameManager.deallocatePageFrame(f1);
    pageFrameManager.deallocatePageFrame(f2);
}