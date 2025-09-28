cmake_minimum_required(VERSION 3.15)
project(ChessProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Release build type par défaut
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

# Ajout des sous-projets
add_subdirectory(chess)
add_subdirectory(game)
