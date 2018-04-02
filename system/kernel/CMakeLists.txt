project(myos-system-kernel LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles -fno-builtin -nostdlib -nostdinc -m32 -masm=intel -fPIE -mno-red-zone")

add_executable(kernel
        src/main.c
        src/hal/gdt.c
        src/hal/idt.c
        src/hal/io.h
        src/hal/asmutil.h
        src/floppy/floppy.c
        src/screen/vga.c
        src/shell.c
        src/keyboard/scanCode.c
        src/keyboard/key.h
        src/filesystem/fat12.c
        src/filesystem/file.c
        src/syscall/syscall.c
        )

add_custom_command(TARGET kernel
        POST_BUILD
        COMMAND strip ARGS ${CMAKE_CURRENT_BINARY_DIR}/kernel)

target_link_libraries(kernel
        stdlib)