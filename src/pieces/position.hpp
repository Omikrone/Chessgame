#pragma once

#include <cstdint>


struct Position
{
    std::int8_t x;
    std::int8_t y;

    bool operator==(const Position &other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
};