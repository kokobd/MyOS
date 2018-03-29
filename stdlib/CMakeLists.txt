project(myos-stdlib LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_library(stdlib STATIC
        src/floppy.c
        src/stdio.c)

target_compile_options(stdlib BEFORE
        PUBLIC -fno-builtin
        PUBLIC -nostdlib
        PUBLIC -nostdinc
        PUBLIC -m32
        PUBLIC -fPIC
        PRIVATE -masm=intel
        )

target_include_directories(stdlib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE src
        )

