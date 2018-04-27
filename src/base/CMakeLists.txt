cmake_minimum_required(VERSION 3.9)
project(myos-base LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(LIB_SOURCES
        src/ctype.cpp
        src/string.cpp
        src/collections/BitSet.cpp
        include/myos/base/collections/BitSet.hpp
        include/myos/base/memory.hpp
        src/memory.cpp
        include/myos/base/memory/Heap.hpp
        include/myos/base/memory/SimpleHeap.hpp
        src/memory/SimpleHeap.cpp
        )

set(TEST_SOURCES
        test/main.cpp
        test/cstring.cpp
        test/ctype.cpp
        test/collections/BitSet.cpp
        test/collections/Queue.cpp
        test/collections/Stack.cpp
        test/memory.cpp
        test/memory/SimpleHeap.cpp
        )

if (PROFILE MATCHES UNIT_TEST)
    add_library(base STATIC
            ${LIB_SOURCES}
            )

    target_compile_definitions(base
            PRIVATE UNIT_TEST
            )
    target_include_directories(base
            PUBLIC include
            PRIVATE src
            )

    add_executable(base-test ${TEST_SOURCES})
    target_link_libraries(base-test
            PRIVATE catch2 base
            )
    add_test(base-test base-test)
else ()
    add_library(base STATIC
            ${LIB_SOURCES}
            src/runtime.cpp
            )

    target_include_directories(base
            PUBLIC include include_std
            PRIVATE src
            )
    target_compile_options(base
            PUBLIC $<$<COMPILE_LANGUAGE:C>:-m32 -masm=intel -ffreestanding -fno-stack-protector>
            PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-m32 -masm=intel -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti>
            )
endif ()


