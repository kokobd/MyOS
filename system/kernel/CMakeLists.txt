project(myos-system-kernel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(kernel
        src/main.cpp
        src/hal/gdt.cpp
        src/hal/idt.cpp
        src/hal/io.hpp
        src/floppy/floppy.cpp
        src/screen/vga.cpp
        src/shell.cpp
        src/keyboard/scanCode.cpp
        src/keyboard/key.hpp
        src/keyboard/input.cpp
        src/filesystem/fat12.cpp
        src/filesystem/file.cpp
        src/syscall/syscall.cpp
        src/exec/elf32.cpp
        )

target_compile_options(kernel
        PRIVATE -m32
        PRIVATE -masm=intel
        PRIVATE -mno-red-zone
        PRIVATE -ffreestanding
        PRIVATE -fno-stack-protector
        PRIVATE -fno-exceptions
        PRIVATE -fno-rtti
        )

set_target_properties(kernel PROPERTIES
        LINK_FLAGS "-nostdlib -m32 -ffreestanding -Wl,-Ttext=0x100400")

target_link_libraries(kernel
        stdlibcpp)