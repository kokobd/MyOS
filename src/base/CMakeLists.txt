cmake_minimum_required(VERSION 3.9)
project(myos-base LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(base STATIC
        src/ctype.cpp
        src/string.cpp
        )
if (PROFILE MATCHES UNIT_TEST)
    target_compile_definitions(base
            PRIVATE UNIT_TEST
            )
    target_include_directories(base
            PUBLIC include
            PRIVATE src
            )

    add_executable(base-test
            test/main.cpp
            test/cstring.cpp
            )
    target_link_libraries(base-test
            PRIVATE catch2 base
            )
    add_test(base-test base-test)
else ()
    target_include_directories(base
            PUBLIC include include_std
            PRIVATE src
            )
    target_compile_options(base
            PUBLIC $<$<COMPILE_LANGUAGE:C>:-m32 -masm=intel -ffreestanding -fno-stack-protector>
            PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-m32 -masm=intel -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti>
            )
endif ()


