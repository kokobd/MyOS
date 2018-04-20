project(myos-apps LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}\
    -ffreestanding -nostdlib -nostartfiles -m32 -masm=intel -fPIE")

add_executable(spin
        spin.c
        )
target_link_libraries(spin
        stdlibc
        )

add_executable(ksapp
        ksapp.c
        )
target_link_libraries(ksapp
        stdlibc
        )
