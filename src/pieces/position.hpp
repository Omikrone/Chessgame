#pragma once

#include <cstdint>
#include <iostream>


struct Position
{
    std::int8_t file;
    std::int8_t rank;

    bool operator==(const Position &other) const {
        return file == other.file && rank == other.rank;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }

    void print() const {
        std::cout << "{" << static_cast<int>(file) << ", " << static_cast<int>(rank) << "}";
    }
};