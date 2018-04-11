project(myos-stdlibcpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
        src/Runtime.cpp
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
