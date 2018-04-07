project(myos-system-kernel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

enable_language(ASM_NASM)

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf32 -o <OBJECT> <SOURCE>")

get_cmake_property(_variableNames VARIABLES)
list(SORT _variableNames)
foreach (_variableName ${_variableNames})
    message(STATUS "${_variableName}=${${_variableName}}")
endforeach ()

add_executable(kernel
        src/multiboot.asm
        src/kernel_start.asm
        src/main.cpp

        include/myos/kernel/Kernel.hpp
        src/Kernel.cpp

        include/myos/kernel/cpu/CPU.hpp
        src/cpu/CPU.cpp

        include/myos/kernel/cpu/GDT.hpp

        include/myos/kernel/cpu/IDT.hpp
        src/cpu/IDT.cpp

        include/myos/kernel/cpu/InterruptHandler.hpp

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
        PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-m32 -masm=intel -mno-red-zone -ffreestanding -fno-stack-protector -fno-exceptions -fno-rtti>
        )

target_include_directories(kernel
        PRIVATE include)

set_target_properties(kernel PROPERTIES
        LINK_FLAGS "-nostdlib -m32 -ffreestanding -Wl,-T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld"
        LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
        )
#        LINK_FLAGS "-nostdlib -m32 -ffreestanding -Wl,-Ttext=0x100400,--verbose")

target_link_libraries(kernel
        stdlibcpp)