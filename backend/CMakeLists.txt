cmake_minimum_required(VERSION 3.15)
project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Release build type per default
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# ----------------------------
# OS detection
# ----------------------------
if(WIN32)
    message(STATUS "Compiling on Windows")
    set(PLATFORM_WINDOWS TRUE)
elseif(UNIX)
    message(STATUS "Compiling on Linux/Mac")
    set(PLATFORM_LINUX TRUE)
endif()

# ----------------------------
# Compiling flags
# ----------------------------
if(MSVC)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    target_compile_options(chess PRIVATE /W4)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread")
endif()

# ----------------------------
# Dependencies
# ----------------------------
# Threads
find_package(Threads REQUIRED)

# ZLIB
find_package(ZLIB REQUIRED)

# OpenSSL
find_package(OpenSSL REQUIRED)

# Boost
if(PLATFORM_WINDOWS)
    find_package(Boost REQUIRED)
else()
    find_package(Boost REQUIRED COMPONENTS system filesystem)
endif()

# Crow
find_package(Crow CONFIG REQUIRED)

# ----------------------------
# Sources et executable
# ----------------------------
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(chess ${SOURCES})

# Include directory
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src)
target_include_directories(chess PRIVATE ${PROJECT_INCLUDE_DIR})

# Link dependencies
target_link_libraries(chess
    PRIVATE
        Threads::Threads
        ZLIB::ZLIB
        OpenSSL::SSL
        OpenSSL::Crypto
        Boost::boost
        Crow::Crow
)

# ----------------------------
# Windows specific options
# ----------------------------
if(PLATFORM_WINDOWS)
    # If using vcpkg
    if(DEFINED ENV{VCPKG_ROOT})
        message(STATUS "VCPKG_ROOT detected: $ENV{VCPKG_ROOT}")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
endif()
