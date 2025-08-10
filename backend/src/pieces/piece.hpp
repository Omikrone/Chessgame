#pragma once

#include <sys/types.h>
#include <vector>

#include "position.hpp"
#include "color.hpp"
#include "move.hpp"
#include "type.hpp"


class Piece {
public:

    Type _pieceType;
    Position _position;
    Color _color;
    bool _hasMoved = false;

    Piece(Type pieceType, const Position& position, Color color)
        : _pieceType(pieceType), _position(position), _color(color) {}

    virtual Piece *clone() const = 0;

    virtual ~Piece() = default;

    virtual char toFEN() const = 0;
    virtual std::vector<std::vector<Position>> getPossibleMoves() const = 0;
};