project(myos-stdlibc LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(PUBLIC_HEADERS
        include/stdio.h
        include/string.h
        include/stdlib.h
        include/ctype.h
        include/sys/syscall.h
        )

add_library(stdlibc STATIC
        src/stdio.c
        src/string.c
        src/ctype.c
        src/crt.c
        src/sys/syscall.c
        ${PUBLIC_HEADERS}
        )
target_compile_options(stdlibc
        PRIVATE -m32
        PRIVATE -masm=intel
        PRIVATE -fPIC
        PRIVATE -ffreestanding
        )

target_include_directories(stdlibc
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE src
        )

