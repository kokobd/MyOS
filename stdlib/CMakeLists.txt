project(myos-stdlib LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-builtin -nostdlib -nostdinc -m32 -masm=intel -fPIC")

set(PUBLIC_HEADERS
        include/stdbool.h
        include/stdint.h
        include/stdio.h
        include/string.h
        include/stdlib.h
        include/ctype.h
        include/sys/syscall.h
        )

add_library(stdlib STATIC
        src/floppy.c
        src/stdio.c
        src/string.c
        src/ctype.c
        src/crt.c
        src/sys/syscall.c
        ${PUBLIC_HEADERS}
        )

target_include_directories(stdlib
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
        PRIVATE src
        )

