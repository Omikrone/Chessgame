cmake_minimum_required(VERSION 3.15)
project(ChessEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Si aucun build type défini → Release par défaut
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Trouver dépendances via vcpkg
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost CONFIG REQUIRED)
find_package(Crow CONFIG REQUIRED)

# Répertoires d'includes du projet
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(chess ${SOURCES})

# Lier dépendances
target_link_libraries(chess
    PRIVATE
        Threads::Threads
        ZLIB::ZLIB
        OpenSSL::SSL
        OpenSSL::Crypto
        Boost::boost
        Crow::Crow
)

# Inclure ton dossier "include/"
target_include_directories(chess PRIVATE ${PROJECT_INCLUDE_DIR})

# Options warnings selon compilateur
if(MSVC)
    target_compile_options(chess PRIVATE /W4)
else()
    target_compile_options(chess PRIVATE -Wall -Wextra -pedantic)
endif()
