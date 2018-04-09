project(myos-stdlibcpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        src/Runtime.cpp
        include/ext/Queue.hpp
        )

add_library(stdlibcpp STATIC
        ${SOURCES}
        )
target_compile_options(stdlibcpp
        PRIVATE -m32
        PRIVATE -masm=intel
        PRIVATE -fPIC
        PRIVATE -ffreestanding
        )

target_include_directories(stdlibcpp
        PUBLIC include
        PRIVATE src
        )

target_link_libraries(stdlibcpp
        PUBLIC stdlibc
        )

add_executable(stdlibcpp-ext-test
        test/main.cpp
        test/QueueTest.cpp
        )
target_include_directories(stdlibcpp-ext-test
        PUBLIC include/ext
        PRIVATE test
        )
target_link_libraries(stdlibcpp-ext-test
        catch2
        )
add_test(stdlibcpp-test stdlibcpp-test)