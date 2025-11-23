cmake_minimum_required(VERSION 3.15)
project(chessgame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
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
# Sources du jeu
# ----------------------------
file(GLOB_RECURSE GAME_SOURCES "src/*.cpp")

# ----------------------------
# Exécutable
# ----------------------------
add_executable(chessgame ${GAME_SOURCES})
target_include_directories(chessgame PRIVATE src)

# ----------------------------
# Options de compilation
# ----------------------------
if(MSVC)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    target_compile_options(chessgame PRIVATE /W4)
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pthread")
endif()

# ----------------------------
# Dépendances externes
# ----------------------------
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

if(PLATFORM_WINDOWS)
    find_package(Boost REQUIRED)
else()
    find_package(Boost REQUIRED COMPONENTS system filesystem)
endif()

include(FetchContent)
FetchContent_Declare(
  crow
  GIT_REPOSITORY https://github.com/CrowCpp/Crow.git
  GIT_TAG v1.2.0
)
FetchContent_MakeAvailable(crow)

include(FetchContent)
FetchContent_Declare(
  httplib
  GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
  GIT_TAG v0.27.0
)

FetchContent_MakeAvailable(httplib)

# ----------------------------
# Lien avec libs
# ----------------------------
target_link_libraries(chessgame
    PRIVATE
        chess
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
    if(DEFINED ENV{VCPKG_ROOT})
        message(STATUS "VCPKG_ROOT detected: $ENV{VCPKG_ROOT}")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
    endif()
endif()