#pragma once

#include <cstdint>
#include <iostream>


struct Square
{
    int8_t file;
    int8_t rank;

    bool operator==(const Square &other) const {
        return file == other.file && rank == other.rank;
    }

    bool operator!=(const Square& other) const {
        return !(*this == other);
    }

    void print() const {
        std::cout << "{" << static_cast<int>(file) << ", " << static_cast<int>(rank) << "}";
    }
};