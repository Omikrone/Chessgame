cmake_minimum_required(VERSION 3.15)

# -------------------------------------------------------------------
# VCPKG toolchain
# -------------------------------------------------------------------
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE
        "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
    message(STATUS "Using VCPKG toolchain: $ENV{VCPKG_ROOT}")
endif()

project(chessgame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-warnings-as-errors=*")

# -------------------------------------------------------------------
# Build type
# -------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Defaulting to build type: Release")
endif()

# -------------------------------------------------------------------
# OS detection
# -------------------------------------------------------------------
if(WIN32)
    set(PLATFORM_WINDOWS TRUE)
    message(STATUS "Platform: Windows")
elseif(UNIX)
    set(PLATFORM_LINUX TRUE)
    message(STATUS "Platform: Linux / macOS")
endif()

# -------------------------------------------------------------------
# Chessboard engine (chess library)
# -------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
  chess
  GIT_REPOSITORY https://github.com/Omikrone/Chessboard
  GIT_TAG v1.4.0
)
FetchContent_MakeAvailable(chess)

# -------------------------------------------------------------------
# Crow framework
# -------------------------------------------------------------------
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.2.0
)
FetchContent_MakeAvailable(crow)

# -------------------------------------------------------------------
# Websocket++
# -------------------------------------------------------------------
FetchContent_Declare(
  websocketpp
  GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
)
FetchContent_MakeAvailable(websocketpp)

# -------------------------------------------------------------------
# External dependencies
# -------------------------------------------------------------------
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

if(PLATFORM_WINDOWS)
    find_package(Boost REQUIRED COMPONENTS random)
else()
    find_package(Boost REQUIRED COMPONENTS system filesystem random)
endif()

# -------------------------------------------------------------------
# Sources
# -------------------------------------------------------------------
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

# -------------------------------------------------------------------
# Executable
# -------------------------------------------------------------------
add_executable(chessgame ${GAME_SOURCES})
message(STATUS "Including: ${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(chessgame
    PRIVATE
        src
)

# -------------------------------------------------------------------
# Compilation options
# -------------------------------------------------------------------
if(MSVC)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    target_compile_options(chessgame PRIVATE /W4)
else()
    target_compile_options(chessgame PRIVATE -Wall -Wextra -pedantic -pthread)
endif()

# -------------------------------------------------------------------
# Linking
# -------------------------------------------------------------------
target_link_libraries(chessgame
    PRIVATE
        chess
        Threads::Threads
        ZLIB::ZLIB
        OpenSSL::SSL
        OpenSSL::Crypto
        Boost::boost
        Boost::random
        Crow::Crow
)

target_include_directories(chessgame PRIVATE
    ${websocketpp_SOURCE_DIR}
)
