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
set_target_properties(spin PROPERTIES
        LINK_FLAGS "-m32 -nostdlib -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
        )

add_executable(ksapp
        ksapp.c
        )
target_link_libraries(ksapp
        stdlibc
        )
set_target_properties(ksapp PROPERTIES
        LINK_FLAGS "-m32 -nostdlib -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
        )

add_executable(ksapp2
        ksapp2.c
        )
target_link_libraries(ksapp2
        stdlibc
        )
set_target_properties(ksapp2 PROPERTIES
        LINK_FLAGS "-m32 -nostdlib -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
        )

add_executable(spin2
        spin2.c
        )
target_link_libraries(spin2
        stdlibc
        )
set_target_properties(spin2 PROPERTIES
        LINK_FLAGS "-m32 -nostdlib -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
        )
