project(myos-system-bootloader LANGUAGES C ASM)

set(CMAKE_C_STANDARD 99)

enable_language(ASM_NASM)

if (NOT CMAKE_ASM_NASM_COMPILER_LOADED)
    message(FATAL_ERROR "Can not find nasm. Please install it.")
endif ()

set(CAN_USE_ASSEMBLER TRUE)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/bootloader
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/stage1.s
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
        COMMAND nasm -f bin -o ${CMAKE_CURRENT_BINARY_DIR}/bootloader stage1.s
)

add_custom_target(bootloader ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/bootloader)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/krnldr.sys
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/stage2.s
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src
        COMMAND nasm -f bin -o ${CMAKE_CURRENT_BINARY_DIR}/krnldr.sys stage2.s
)

add_custom_target(krnldr ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/krnldr.sys)
