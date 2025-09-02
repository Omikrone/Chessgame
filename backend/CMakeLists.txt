cmake_minimum_required(VERSION 3.10)
project(ChessEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Crow REQUIRED)

file(GLOB SOURCES "src/*.cpp")

add_executable(chess ${SOURCES})

target_link_libraries(chess PRIVATE Crow::Crow)

target_compile_options(chess PRIVATE /W4)
