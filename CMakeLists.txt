cmake_minimum_required(VERSION 3.9)

project(myos LANGUAGES C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(dependencies/catch2-cmake)

enable_testing()

add_subdirectory(stdlibc)
add_subdirectory(stdlibcpp)
add_subdirectory(system)
add_subdirectory(apps)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/myos.img
        DEPENDS clear file welcome kernel
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ./scripts/bundle.sh ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(myos-image ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/myos.img)
