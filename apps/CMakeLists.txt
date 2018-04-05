project(myos-apps LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -ffreestanding -nostdlib -nostartfiles -m32 -masm=intel -fPIE")

add_executable(file file.c)
target_link_libraries(file stdlibc)

add_executable(clear clear.c)
target_link_libraries(clear stdlibc)

add_executable(welcome welcome.c)
target_link_libraries(welcome stdlibc)