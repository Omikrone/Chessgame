#pragma once

#include <sys/types.h>
#include <vector>

#include "position.hpp"
#include "color.hpp"
#include "move.hpp"


class Piece {
public:

    Position _position;
    Color _color;

    Piece(const Position& position, Color color)
        : _position(position), _color(color) {}

    virtual ~Piece() = default;

    virtual char symbol() const = 0;
    virtual std::vector<Position> getPossibleMoves() const = 0;
};