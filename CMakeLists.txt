cmake_minimum_required(VERSION 3.9)

project(myos LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

if (PROFILE MATCHES UNIT_TEST)
    add_subdirectory(deps/catch2-cmake)
endif ()

enable_testing()

add_subdirectory(src/base)
add_subdirectory(src/kernel)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/myos.img
        DEPENDS kernel scripts/bundle.sh
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ./scripts/bundle.sh ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(myos-image ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/myos.img)
