cmake_minimum_required(VERSION 3.20)
project(KytyPS5-Lite VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(KYTY_ENABLE_VULKAN "Enable Vulkan backend" ON)
option(KYTY_BUILD_TESTS "Build unit tests" OFF)

# Find Vulkan
if(KYTY_ENABLE_VULKAN)
    find_package(Vulkan REQUIRED)
endif()

# Core library
add_library(kyty_core STATIC
    src/common/log.cpp
    src/common/memory.cpp
    src/cpu/cpu.cpp
    src/graphics/host_gpu.cpp
    src/graphics/guest_gpu.cpp
    src/graphics/shader_recompiler/recompiler.cpp
    src/kernel/kernel.cpp
    src/kernel/libkernel.cpp
    src/loader/elf_loader.cpp
    src/audio/audio.cpp
)

target_include_directories(kyty_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(KYTY_ENABLE_VULKAN)
    target_link_libraries(kyty_core PUBLIC Vulkan::Vulkan)
    target_compile_definitions(kyty_core PUBLIC KYTY_ENABLE_VULKAN=1)
endif()

# Main executable
add_executable(kyty_emulator src/main.cpp)
target_link_libraries(kyty_emulator PRIVATE kyty_core)

# Tests
if(KYTY_BUILD_TESTS)
    enable_testing()
    add_executable(kyty_tests tests/cpu_test.cpp tests/memory_test.cpp)
    target_link_libraries(kyty_tests PRIVATE kyty_core)
    add_test(NAME kyty_unit_tests COMMAND kyty_tests)
endif()
