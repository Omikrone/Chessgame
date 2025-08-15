#pragma once

#include <sys/types.h>
#include <vector>

#include "utils/position.hpp"
#include "utils/color.hpp"
#include "utils/move.hpp"
#include "utils/type.hpp"


class Piece {
public:

    Type _pieceType;
    Square _position;
    Color _color;
    bool _hasMoved = false;

    Piece(Type pieceType, const Square& position, Color color)
        : _pieceType(pieceType), _position(position), _color(color) {}

    virtual Piece *clone() const = 0;

    virtual ~Piece() = default;

    virtual char toFEN() const = 0;
    virtual std::vector<std::vector<Square>> getRawMoves() const = 0;
};