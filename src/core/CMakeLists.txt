cmake_minimum_required(VERSION 3.9)
project(myos-core LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(LIB_SOURCES
        src/ctype.cpp
        src/string.cpp
        src/collections/BitSet.cpp
        include/myos/core/collections/BitSet.hpp
        include/myos/core/memory.hpp
        src/memory.cpp
        include/myos/core/memory/Heap.hpp
        include/myos/core/memory/SimpleHeap.hpp
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
    add_library(core STATIC
            ${LIB_SOURCES}
            )

    target_compile_definitions(core
            PRIVATE UNIT_TEST
            )
    target_include_directories(core
            PUBLIC include
            PRIVATE src
            )

    add_executable(core-test ${TEST_SOURCES})
    target_link_libraries(core-test
            PRIVATE catch2 core
            )
    add_test(core-test core-test)
else ()
    add_library(core STATIC
            ${LIB_SOURCES}
            src/runtime.cpp
            )

    target_include_directories(core
            PUBLIC include include_std
            PRIVATE src
            )
    target_compile_options(core
            PUBLIC $<$<COMPILE_LANGUAGE:C>:-m32 -masm=intel -ffreestanding -fno-stack-protector>
            PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-m32 -masm=intel -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti>
            )
endif ()


