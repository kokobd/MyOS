cmake_minimum_required(VERSION 3.9)
project(myos-base LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

add_library(base STATIC
        src/ctype.c
        include/ctype.h

        src/string.c
        include/string.h

        include/cctype
        include/cstddef
        include/cstdint
        include/cstring
        )
target_compile_options(base
        PUBLIC $<$<COMPILE_LANGUAGE:C>:-m32 -masm=intel -ffreestanding -fno-stack-protector>
        PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-m32 -masm=intel -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti>
        )
target_include_directories(base
        PUBLIC include
        PRIVATE src
        )
