cmake_minimum_required(VERSION 3.15)
project(ChessProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Release build type par défaut
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

include(FetchContent)
FetchContent_Declare(
  chess
  GIT_REPOSITORY https://github.com/Omikrone/Chessboard
  GIT_TAG main
)
FetchContent_MakeAvailable(chess)

# Ajout des sous-projets
add_subdirectory(game)
