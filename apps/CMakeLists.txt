project(myos-apps LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -fno-builtin -nostdlib -nostdinc -nostartfiles -m32 -masm=intel -fPIE")

add_executable(app1 app1.c)
target_link_libraries(app1
        stdlib)